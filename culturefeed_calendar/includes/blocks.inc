<?php
/**
 * @file
 * Blocks for the calendar module.
 */

/**
 * Render a block with event types as facet items.
 */
function culturefeed_calendar_block_event_types() {

  // Get the allowed options for the event facet.
  $eventtypes = variable_get('calendar_facet_event_types', array());
  if (empty($eventtypes)) {
    return;
  }

  $facet_name = 'category_eventtype_id';
  $domain_id = 'eventtype'; //'eventtype';
  $allowed_values = $eventtypes;
  $block_settings = array(
    'sort' => variable_get('culturefeed_search_sort_facet-eventtype', CULTUREFEED_SEARCH_SORT_ALPHABETICALLY),
    'highest_level' => 2,
    'show_subitems' => FALSE,
    'intersect' => 1,
  );
  module_load_include('inc', 'culturefeed_search_ui', 'includes/blocks');
  $block = culturefeed_search_ui_search_facets_block($facet_name, $domain_id, $allowed_values, $block_settings);

  return $block;

}

/**
 * Render a custom filter form as facets for the calendar.
 */
function culturefeed_calendar_block_filter_form(\Cultuurnet\Search\SearchResult $search_result) {

  $variable_name = 'culturefeed_calendar_filter_options';
  $filter_options = variable_get($variable_name, culturefeed_search_ui_default_filter_options());

  $display_type = variable_get('culturefeed_calendar_filter_display_options', 'links');
  $filter_options = array_filter($filter_options, function($option) {
    return !isset($option['exposed']) || !empty($option['exposed']);
  });

  $block = array();
  if (!empty($filter_options)) {
    module_load_include('inc', 'culturefeed_search_ui', 'includes/blocks');
    $build = culturefeed_search_ui_block_filter_block($filter_options, $display_type);
    // Renderable array.
    if (is_array($build)) {
      $block['content'] = $build;
    }
    // Create a renderable array for the strings.
    else {
      $block['content'] = array('#markup' => $build);
    }

  }

  return $block;

}
