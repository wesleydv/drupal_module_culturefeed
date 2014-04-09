<?php

/**
 * @file
 * Views integration.
 */

/**
 * Implements hook_views_data().
 */
function culturefeed_search_views_data() {

  $data = array();
  $data['cdb_items'] = culturefeed_search_views_data_cdb_items();
  $data['cdb_items_page'] = culturefeed_search_views_data_cdb_items_page();

  return $data;

}

/**
 * Implements hook_views_plugins().
 */
function culturefeed_search_views_views_plugins() {

  $path = drupal_get_path('module', 'culturefeed_search_views') . '/views';

  return array(
    'module' => 'culturefeed_search_views',
    'query' => array(
      'culturefeed_search_views_query' => array(
        'uses fields' => TRUE,
        'path' => $path . '/plugins',
        'title' => t('Culturefeed Search Query'),
        'help' => t('Query that allows you to search with culturefeed.'),
        'handler' => 'culturefeed_search_views_query',
        'parent' => 'views_query',
      ),
      'culturefeed_search_views_query_pages' => array(
        'uses fields' => TRUE,
        'path' => $path . '/plugins',
        'title' => t('Culturefeed Search Query: Pages'),
        'help' => t('Query that allows you to search with culturefeed pages.'),
        'handler' => 'culturefeed_search_views_query_pages',
        'parent' => 'culturefeed_search_views_query',
      ),
    ),
    'row' => array(
      'cdb_items' => array(
        'title' => t('Culturefeed cdb items'),
        'handler' => 'culturefeed_search_views_row_cdb',
        'path' => $path . '/plugins',
        'base' => array('cdb_items', 'cdb_items_page'),
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
  );

}

/**
 * Get the views data for normal cdb items.
 */
function culturefeed_search_views_data_cdb_items() {

  $data = array();

  $data['table']['group'] = t('Cdb items: events, actors, productions');
  $data['table']['base'] = array(
    'field' => 'cdbid',
    'title' => t('Cdb item: event, actor or production'),
    'query class' => 'culturefeed_search_views_query',
  );

    // Filter on a custom query
  $data['q'] = array(
    'title' => t('Query'),
    'help' => t('Perform a free text search.'),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_q',
    ),
  );

  // Filter on group.
  $data['group'] = array(
    'title' => t('Group'),
    'help' => t('Add a group filter'),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_group',
    ),
  );

  // Add filter on category per category type.
  $domains = culturefeed_search_get_domains();
  foreach ($domains as $did => $label) {
    $data['domain_' . $did] = array(
      'title' => t('Category: @domain', array('@domain' => $label)),
      'help' => t('Perform a search on category of this type.'),
      'filter' => array(
        'handler' => 'views_handler_filter_culturefeed_search_category',
      ),
    );
  }

  // Type
  $data['type'] = array(
    'title' => t('Type'),
    'help' => t('Type of the cdb item'),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_type',
    ),
  );

  // Cdbid field
  $data['cdbid'] = array(
    'title' => t('Cdbid'),
    'help' => t('Id of the cdb item'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_id',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_filter_query',
    ),
  );

  // Title field
  $data['title'] = array(
    'title' => t('Title'),
    'help' => t('Title of the cdb item'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_title',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_filter_query',
    ),
  );

  // City field.
  $data['city'] = array(
    'title' => t('City'),
    'help' => t('Perform a search on a city.'),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_city',
    ),
  );

  // Created by field.
  $data['createdby'] = array(
    'title' => t('Created by'),
    'help' => t('Perform a search created by certain user'),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_createdby',
    ),
  );

  // Created by field.
  $data['createdbycurrentuser'] = array(
    'title' => t('Created by current user'),
    'help' => t('Perform a search created by current user'),
    'filter' => array(
      'handler' =>
      'views_handler_filter_culturefeed_search_createdbycurrentuser',
    ),
  );

  // Filter on location name.
  $data['location_label'] = array(
    'title' => t('Location name'),
    'help' => t('Perform a search on the location name.'),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_filter_query',
    ),
  );

  // Filter on agefrom.
  $data['agefrom'] = array(
    'title' => t('Agefrom'),
    'help' => t('Perform a search on minimum required age.'),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_agefrom',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_culturefeed_search_agefrom',
    ),
  );

  // Filter on organiser.
  $data['organiser_label'] = array(
    'title' => t('Organiser'),
    'help' => t('Perform a search on organiser name.'),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_filter_query',
    ),
  );

  // Filter on free event.
  $data['free'] = array(
    'title' => t('Free event'),
    'help' => t('Perform a search on free events.'),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_free',
    ),
  );

  // Filter on dates
  $data['datetype'] = array(
    'title' => t('Date type'),
    'help' => t('Perform a search on a predefined type of date query'),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_datetype',
    ),
  );

  $data['date'] = array(
    'title' => t('Date'),
    'help' => t('Perform a search on a date'),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_daterange',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_culturefeed_search_date',
    ),
  );

  // Fields.
  // Short Description.
  $data['description'] = array(
    'title' => t('Short Description'),
    'help' => t('Short Description of the cdb item'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_short_description',
    ),
  );

  // Location.
  $data['location'] = array(
    'title' => t('Location'),
    'help' => t('Location of the cdb item'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_location',
    ),
  );

  // Picture.
  $data['picture'] = array(
    'title' => t('Picture'),
    'help' => t('Picture of the cdb item'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_picture',
    ),
  );

  // Calendar summary.
  $data['when'] = array(
    'title' => t('Calendar summary'),
    'help' => t('Summary of the calendar'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_calendar_summary',
    ),
  );

  // Organiser.
  $data['organiser'] = array(
    'title' => t('Organiser'),
    'help' => t('Organiser of the cdb item'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_organiser',
    ),
  );

  $data['link'] = array(
    'title' => t('Link'),
    'help' => t('Link to the cdb item'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_link',
    ),
  );

  $data['lastupdated'] = array(
    'title' => t('Last updated'),
    'help' => t('Last updated date/time of the cdb item'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_lastupdated',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_culturefeed_search_date',
    ),
  );

  // Sorts
  $data['recommend_count'] = array(
    'title' => t('Total recommend'),
    'help' => t('Sort on recommend count.'),
    'sort' => array(
      'handler' => 'views_handler_sort_culturefeed_search_base',
    ),
  );

  $data['comment_count'] = array(
    'title' => t('Total comments'),
    'help' => t('Sort on comment count.'),
    'sort' => array(
      'handler' => 'views_handler_sort_culturefeed_search_base',
    ),
  );

  return $data;
}

/**
 * Get the views data for page cdb items.
 */
function culturefeed_search_views_data_cdb_items_page() {

  $data = array();
  $data['table']['group'] = t('Cdb items: pages');
  $data['table']['base'] = array(
    'field' => 'cdbid',
    'title' => t('Cdb item: page'),
    'query class' => 'culturefeed_search_views_query_pages',
  );

  // Fields.
  // Cdbid field
  $data['cdbid'] = array(
    'title' => t('Cdbid'),
    'help' => t('Id of the page'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_id',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_filter_query',
    ),
  );

  // Title field.
  $data['title'] = array(
    'title' => t('Name'),
    'help' => t('Name of the page'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_title',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_filter_query',
    ),
  );

  // Link.
  $data['link'] = array(
    'title' => t('Link'),
    'help' => t('Link to the page'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_link',
    ),
  );

  // Short Description.
  $data['description'] = array(
    'title' => t('Description'),
    'help' => t('Description of the page'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_short_description',
    ),
  );

  // Location.
  $data['address'] = array(
    'title' => t('Address'),
    'help' => t('Home address of the page'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_location',
    ),
  );

  // Picture.
  $data['picture'] = array(
    'title' => t('Picture'),
    'help' => t('Picture of the page'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_picture',
    ),
  );

  // Cover.
  $data['cover'] = array(
    'title' => t('Cover'),
    'help' => t('Cover of the page'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_picture',
    ),
  );

  $data['tagline'] = array(
    'title' => t('Tagline'),
    'help' => t('Tagline of the page'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_tagline',
    ),
  );

  $data['categories'] = array(
    'title' => t('Categories'),
    'help' => t('Categories of the page'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_categories',
    ),
  );

  $data['linkWebsite'] = array(
    'title' => t('Link website'),
    'help' => t('Link to website of the page'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_page_link',
    ),
  );

  $data['linkBlog'] = array(
    'title' => t('Link blog'),
    'help' => t('Link to blog of the page'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_page_link',
    ),
  );

  $data['linkYouTube'] = array(
    'title' => t('Link Youtube'),
    'help' => t('Link to Youtube page of the page'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_page_link',
    ),
  );

  $data['linkFacebook'] = array(
    'title' => t('Link Facebook'),
    'help' => t('Link to Facebook page of the page'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_page_link',
    ),
  );

  $data['linkGooglePlus'] = array(
    'title' => t('Link Google+'),
    'help' => t('Link to Google+ page of the page'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_page_link',
    ),
  );

  $data['linkTwitter'] = array(
    'title' => t('Link Twitter'),
    'help' => t('Link to twitter account of the page'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_page_link',
    ),
  );

  $data['linkTicketing'] = array(
    'title' => t('Link Ticketing'),
    'help' => t('Link to ticketing site of the page'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_page_link',
    ),
  );

  $data['email'] = array(
    'title' => t('Email'),
    'help' => t('Contact email of the page'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_email',
    ),
  );

  $data['phone_number'] = array(
    'title' => t('Phone number'),
    'help' => t('Contact phone number of the page'),
    'field' => array(
      'handler' => 'views_handler_field_cdb_item_phone_number',
    ),
  );

  // Filters only.
  // City.
  $data['city'] = array(
    'title' => t('City'),
    'help' => t('Perform a search on a city.'),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_city',
    ),
  );

  // Creation date.
  $data['creationdate'] = array(
    'title' => t('Creation date'),
    'help' => t('The date this page was created.'),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_culturefeed_search_date',
    ),
  );

  // Updated date.
  $data['lastupdated'] = array(
    'title' => t('Last updated'),
    'help' => t('The date this page was last updated.'),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_culturefeed_search_date',
    ),
  );

 // Like count.
  $data['like_count'] = array(
    'title' => t('Total likes'),
    'help' => t('Total amount of times this page was liked.'),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_culturefeed_search_base',
    ),
  );

  // Recommend count.
  $data['recommend_count'] = array(
    'title' => t('Total recommends'),
    'help' => t('Total amount of times this page was recommended.'),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_culturefeed_search_base',
    ),
  );

  // Comment count.
  $data['comment_count'] = array(
    'title' => t('Total comments'),
    'help' => t('Total ammount of times this page was commented on.'),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_culturefeed_search_base',
    ),
  );

 // Page follow count.
  $data['pagefollow_count'] = array(
    'title' => t('Total followers'),
    'help' => t('Total people following this page.'),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_culturefeed_search_base',
    ),
  );

  // Page admin count.
  $data['pageadmin_count'] = array(
    'title' => t('Total admins'),
    'help' => t('Total amount of admins for this page.'),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_culturefeed_search_base',
    ),
  );

  // Page member count.
  $data['pagemember_count'] = array(
    'title' => t('Total members'),
    'help' => t('Total amount of members in this page.'),
    'filter' => array(
      'handler' => 'views_handler_filter_culturefeed_search_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_culturefeed_search_base',
    ),
  );

  // Page member count.
  $data['distance'] = array(
    'title' => t('Distance'),
    'help' => t('Sort on distance to a given point.'),
    'sort' => array(
      'handler' => 'views_handler_sort_culturefeed_search_distance',
    ),
  );

  // Add filter on category per category type.
  $domains = culturefeed_search_get_domains();
  foreach ($domains as $did => $label) {
    $data['domain_' . $did] = array(
      'title' => t('Category: @domain', array('@domain' => $label)),
      'help' => t('Perform a search on category of this type.'),
      'filter' => array(
        'handler' => 'views_handler_filter_culturefeed_search_category',
      ),
    );
  }

  return $data;
}
