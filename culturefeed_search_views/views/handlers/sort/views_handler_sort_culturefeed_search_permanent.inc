<?php

/**
 * @class
 * Handler class for sorting on permanent status.
 */
class views_handler_sort_culturefeed_search_permanent extends views_handler_sort_culturefeed_search_base {

  /**
   * @see views_handler::init()
   */
  function init(&$view, &$options) {
    parent::init($view, $options);
    $this->sort_field = 'permanent';
  }

}