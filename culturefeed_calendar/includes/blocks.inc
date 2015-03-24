<?php
/**
 * @file
 * Blocks for the calendar module.
 */

/**
 * Render a block with event types as facet items.
 */
function culturefeed_calendar_block_event_types() {

  $eventtypes = variable_get('calendar_facet_event_types', array());
  if (empty($eventtypes)) {
    return;
  }

  $query = db_select('culturefeed_search_terms', 'cst');
  $query->fields('cst', array('tid', 'name', 'slug', 'p1'));
  $query->condition("cst.did", "eventtype");
  $query->condition("cst.language", culturefeed_search_get_preferred_language());
  $db_or = db_or();
  $db_or->condition('cst.tid', $eventtypes, 'IN');
  $db_or->condition('cst.p1', $eventtypes, 'IN');

  $query->condition($db_or);
  $result = $query->execute();

  $items = array();
  foreach ($result as $row) {
    if (empty($row->p1)) {
      $items[$row->tid]['item'] = $row;
    }
    else {
      $items[$row->p1]['children'][$row->tid]['item'] = $row;
    }
  }

  if (!empty($items)) {
    return array(
      'content' => array(
        '#theme' => 'culturefeed_agenda_event_types',
        '#items' => $items,
      ),
    );
  }

  return;
}

/**
 * Render a custom filter form as facets for the calendar.
 */
function culturefeed_calendar_block_filter_form(\Cultuurnet\Search\SearchResult $search_result) {

  $variable_name = 'culturefeed_calendar_filter_options';
  $filter_options = variable_get($variable_name, culturefeed_search_ui_default_filter_options());

  $display_type = variable_get('culturefeed_calendar_filter_display_options');
  $filter_options = array_filter($filter_options, function($option) {
    return !isset($option['exposed']) || !empty($option['exposed']);
  });

  $block = array();
  if (!empty($filter_options)) {
    $block['content'] = culturefeed_search_ui_block_filter_block($filter_options, $display_type);
  }

  return $block;

}
