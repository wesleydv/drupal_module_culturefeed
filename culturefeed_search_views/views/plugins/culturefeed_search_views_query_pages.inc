<?php
use \CultuurNet\Search\Parameter;

/**
 * @class
 * Views query plugin for culturefeed search api on pages.
 */
class culturefeed_search_views_query_pages extends culturefeed_search_views_query {

  /**
   * Execute the query
   * @see views_plugin_query::execute()
   */
  function execute(&$view) {

    $start = microtime(TRUE);
    $this->prepareExecute();

    $searchService = culturefeed_get_search_service();
    $result = $searchService->searchPages($this->parameters);

    // Give the result to the view.
    $view->result = $result->getItems();
    $view->total_rows = $result->getTotalCount();
    $this->pager->total_items = $result->getTotalCount();
    $this->pager->update_page_info();
    $view->execute_time = microtime() - $start;
  }

}
