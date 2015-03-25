<?php
/**
 * @file
 * Defines a Page callback for Calendar search results for a user.
 */

//use \CultuurNet\Search\Parameter;
use \CultuurNet\Search\Component\Facet;

/**
 * Class CultureFeedMyCalendarPage
 */
class CultureFeedMyCalendarPage extends CultureFeedSearchPage
    implements CultureFeedSearchPageInterface {

  /**
   * Activities.
   * @var Object
   */
  protected $activities = NULL;

  /**
   * userId.
   * @var String
   */
  protected $userId = '';

  /**
   * Initializes the search with data from the URL query parameters.
   */
  public function initialize() {

    if (empty($this->userId)) {
      $this->userId = DrupalCultureFeed::getLoggedInUserId();
    }

    // Only initialize once.
    if (empty($this->facetComponent)) {
      $this->facetComponent = new Facet\FacetComponent();

      // Retrieve search parameters and add some defaults.
      $params = drupal_get_query_parameters();
      $params += array(
        'sort' => $this->getDefaultSort(),
        'search' => '',
        'facet' => array(),
      );

      $this->pageNumber = empty($params['page']) ? 1 : $params['page'] + 1;

      $this->addFacetFilters($params);

      $this->parameters[] = $this->facetComponent->facetField('category');
      //$this->parameters[] = $this->facetComponent->facetField('datetype');
      //$this->parameters[] = $this->facetComponent->facetField('city');
      //$this->parameters[] = $this->facetComponent->facetField('location_category_facility_id');

      $this->execute($params);

      // Warm up cache.
      $this->warmupCache();
    }
  }

  /**
   * Executes query for activities and the user calendar.
   */
  private function executeUserActivities($userId) {

    // Only search for activities with type_like or type_ik_ga.
    $activity_options = array(
      CultureFeed_Activity::TYPE_LIKE,
      CultureFeed_Activity::TYPE_IK_GA,
    );

    $query = new CultureFeed_SearchActivitiesQuery();
    $query->max = 500;
    $query->type = $activity_options;
    $query->contentType = 'event';
    $query->userId = $userId;

    // No search cache for the calendar page.
    global $conf;
    $conf['culturefeed_search_cache_enabled'] = FALSE;

    $this->parameters[] = new CultuurNet\Search\Parameter\Start(($this->pageNumber - 1) * $this->resultsPerPage);
    $this->parameters[] = new CultuurNet\Search\Parameter\Group($this->group);
    $this->parameters[] = new CultuurNet\Search\Parameter\Rows(500);
    $this->parameters[] = new CultuurNet\Search\Parameter\Parameter('spellcheck', 'false');
    $this->parameters[] = new CultuurNet\Search\Parameter\FilterQuery('type:event');
    $this->parameters[] = new CultuurNet\Search\Parameter\Query('*:*');
    $this->parameters[] = new CultuurNet\Search\Parameter\FilterQuery('attend_users:' . $userId . ' OR like_users:' . $userId);

    $searchService = culturefeed_get_search_service();
    $this->facetQueryAlter();
    $this->result = $searchService->search($this->parameters);

    // No likes / attends for this user on future events, don't do an activity search.
    if ($this->result->getTotalCount() == 0) {
      return;
    }

    $items = $this->result->getItems();
    $content_ids = array();
    foreach ($items as $item) {
      $content_ids[] = $item->getId();
    }

    // Only search on found events. This way, we only see events in the future.
    $query->nodeId = $content_ids;

    try {
      $this->activities = DrupalCultureFeed::searchActivities($query);
    }
    catch (Exception $e) {
      watchdog_exception('culturefeed_calendar', $e);
    }

    return $this->activities;

  }

  /**
   * Executes query for activities and anonymous calendar.
   */
  private function executeAnonymousActivities() {

    // No cookie = no activities
    if (isset($_COOKIE['Drupal_visitor_calendar'])) {

      $calendar = json_decode($_COOKIE['Drupal_visitor_calendar']);

      // Check if cookie is valid.
      if (is_array($calendar)) {

        $eventids = $filterids = array();
        foreach ($calendar as $key => $event) {
          $eventids[] = $event->nodeId;
          $filterids[] = '"' . $event->nodeId . '"';
        }

        $this->parameters[] = new CultuurNet\Search\Parameter\Group();
        $this->parameters[] = new CultuurNet\Search\Parameter\Rows(500);
        $this->parameters[] = new CultuurNet\Search\Parameter\FilterQuery('type:event');
        $this->parameters[] = new CultuurNet\Search\Parameter\Query('cdbid IN(' . implode(',', $eventids) . ')');

        try {

          $service = culturefeed_get_search_service();
          $this->facetQueryAlter();
          $this->result = $service->search($this->parameters);
          // No future events in the cookie.
          if ($this->result->getTotalCount() == 0) {
            return;
          }

          $items = $this->result->getItems();

          // Set only the events that are found on search api (=future events).
          foreach ($items as $item) {
            $key = array_search($item->getId(), $eventids);
            if ($key !== FALSE) {
              unset($eventids[$key]);
              $this->activities->objects[] = $calendar[$key];
            }
          }

          // All remaining eventids don't exist in future, remove them of cookie.
          foreach ($eventids as $key => $id) {
            culturefeed_calendar_delete_calendar_event_cookie($calendar[$key]);
          }


        }
        catch (Exception $e) {
          watchdog_exception('culturefeed_calendar', $e);
        }


        $this->activities->total = count($this->activities->objects);

      }

    }

  }

  /**
   * Execute the search for current page.
   */
  protected function execute($params) {

    $this->activities = new stdClass();
    $this->activities->objects = array();
    $this->activities->total = 0;

    // Third page argument is the $user_id for Calendar pages.
    if (!empty($this->userId)) {
      $this->executeUserActivities($this->userId);
    }
    else {
      $this->executeAnonymousActivities();
    }

    // No drupal alter for these queries.

    if (!isset($this->result)) {
      throw new InvalidSearchPageException('No results loaded');
    }
    $this->facetComponent->obtainResults($this->result);

  }

  /**
   * Alter the query for factes.
   */
  protected function facetQueryAlter() {

    // Custom calendar form filter facets.
    culturefeed_search_ui_page_add_query_filters($this,
      variable_get('culturefeed_calendar_filter_options', culturefeed_search_ui_default_filter_options()),
      variable_get('culturefeed_calendar_filter_operator', 'and')
    );

    // Event type facets.

  }

  /**
   * Get the build from current search page.
   */
  protected function build() {

    //pager_default_initialize($this->result->getTotalCount(), $this->resultsPerPage);

    $build = array();

    module_load_include('inc', 'culturefeed_calendar', 'includes/pages');

    if ($this->result->getTotalCount() > 0) {

      $build['pager-container'] =  array(
        '#type' => 'container',
        '#attributes' => array(),
      );

      // Third page argument is the $user_id for Calendar pages.
      if (!empty($this->userId)) {
        $build['pager-container']['list'] = array(
          '#markup' => theme('culturefeed_calendar_page', array('activities' => $this->activities, 'user_id' => $this->userId))
        );
      }
      else {
        $build['pager-container']['list'] = array(
          '#markup' => theme('culturefeed_calendar_page', array('activities' => $this->activities))
        );
      }

    }

    return $build;

  }

  /**
   * @override
   */
  public function setPageArguments($arguments) {
    $this->pageArguments = $arguments;

    if (!empty($arguments[3])) {
      $this->userId = $arguments[3];
    }
  }

  /**
   * {@inheritdoc}
   */
  protected function addFacetFilters($params) {
    parent::addFacetFilters($params);
  }

  /**
   * Get the active trail to show.
   */
  public function getActiveTrail() {

    $active_trail = array();

    $active_trail[] = array(
      'title' => t('Home'),
      'href' => '<front>',
      'link_path' => '',
      'localized_options' => array(),
      'type' => 0,
    );

    $active_trail[] = array(
      'title' => t('Your Account'),
      'href' => 'user',
      'link_path' => '',
      'localized_options' => array(),
      'type' => 0,
    );

    $active_trail[] = array(
      'title' => $this->getPageTitle(),
      'href' => $_GET['q'],
      'link_path' => '',
      'localized_options' => array(),
      'type' => 0,
    );

    return $active_trail;

  }

  /**
   * Warm up static caches that will be needed for this request.
   * We do this before rendering, because data for by example the recommend link would generate 20 requests.
   * This way we can lower this to only 1 request.
   */
  protected function warmupCache() {
    $this->translateFacets();
    $this->prepareSlugs();
  }

  /**
   * Warm up cache for facets to translate the items.
   */
  private function translateFacets() {
    $found_ids = array();
    $found_results = array();
    $translated_terms = array();
    $facets = $this->facetComponent->getFacets();
    foreach ($facets as $key => $facet) {
      // The key should start with 'category_' or 'location_'
      $start = substr($key, 0, 9);
      if (in_array($start, array('category_', 'location_'))) {
        $items = $facet->getResult()->getItems();
        foreach ($items as $item) {
          $found_ids[$item->getValue()] = $item->getValue();
        }
      }
    }

    // Translate the facets.
    if ($translations = culturefeed_search_term_translations($found_ids, TRUE)) {

      // Preferred language.
      $preferred_language = culturefeed_search_get_preferred_language();

      // Translate the facets labels.
      foreach ($facets as $key => $facet) {
        // The key should start with 'category_' or 'location_'
        $start = substr($key, 0, 9);
        if (in_array($start, array('category_', 'location_'))) {
          $items = $facet->getResult()->getItems();
          foreach ($items as $item) {
            // Translate if found.
            if (!empty($translations[$item->getValue()][$preferred_language])) {
              $item->setLabel($translations[$item->getValue()][$preferred_language]);
            }
          }
        }
      }

    }

  }

  /**
   * Prepare slugs for culturefeed_agenda_url_outbound_alter().
   */
  private function prepareSlugs() {
    $term_slugs = &drupal_static('culturefeed_search_term_slugs', array());
    $facets = $this->facetComponent->getFacets();
    $items = array();

    // At the moment we only need slugs for event type and themes.
    if (isset($facets['category_eventtype_id'])) {
      $items = $facets['category_eventtype_id']->getResult()->getItems();
    }
    if (isset($facets['category_theme_id'])) {
      $items = array_merge($items, $facets['category_theme_id']->getResult()->getItems());
    }

    // Search the slug for all facet items.
    if ($items) {

      $preferred_language = culturefeed_search_get_preferred_language();

      // Construct an array with tids to do the query.
      $tids = array();
      foreach ($items as $item) {
        $subitems = $item->getSubItems();
        if ($subitems) {
          foreach ($subitems as $subitem) {
            $tids[] = $subitem->getValue();
          }
        }
        $tids[] = $item->getValue();
      }

      $result = db_query('SELECT tid, slug FROM {culturefeed_search_terms} WHERE tid IN(:tids) AND language = :language', array(':tids' => $tids, ':language' => $preferred_language));
      foreach ($result as $row) {
        $term_slugs[$row->tid] = $row->slug;
      }
    }

  }

  /**
   * Gets a page description for all pages.
   *
   * Only type aanbod UiT domein, theme and location need to be prepared for search engines.
   *
   * @see culturefeed_search_ui_search_page()
   *
   * @return string
   *   Description for this type of page.
   */
  public function getPageDescription() {
    return t("A summary of all events in your calendar");
  }

}
