<?php

/**
 * @file
 * Theme implementations for Culturefeed uitpas.
 */

/**
 * Implements hook_theme().
 */
function culturefeed_uitpas_theme() {
  return array(
    'culturefeed_uitpas_advantage' => array(
      'variables' => array('advantage' => NULL),
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
      'file' => 'theme.inc',
      'template' => 'culturefeed-uitpas-advantage',
    ),
    'culturefeed_uitpas_advantages' => array(
      'variables' => array(
        'advantages' => array(),
        'advantages_total' => 0,
        'advantages_pager_element' => 0,
      ),
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
      'file' => 'theme.inc',
      'template' => 'culturefeed-uitpas-advantages',
    ),
    'culturefeed_uitpas_advantages_table' => array(
      'variables' => array(
        'title' => t('Advantages'),
        'advantages' => array(),
        'advantages_total' => 0,
        'advantages_pager_element' => 0,
        'items' => array(),
        'pager' => FALSE,
      ),
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
      'template' => 'culturefeed-uitpas-advantages-table',
      'file' => 'theme.inc',
    ),
    'culturefeed_uitpas_event_details_advantages' => array(
      'file' => 'theme.inc',
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
      'template' => 'culturefeed-uitpas-event-details-advantages',
      'variables' => array(
        'title' => '',
        'show_all_link_title' => '',
        'show_all_link_path' => '',
        'show_all_link_default_render' => '',
        'promotions' => array(),
        'promotions_array' => array(),
        'promotions_default_render' => '',
      ),
    ),
    'culturefeed_uitpas_event_price_classes' => array(
      'variables' => array(
        'price_classes' => array(),
        'price_classes_array' => array(),
        'price_classes_default_render' => '',
        'reduced' => FALSE,
      ),
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
      'file' => 'theme.inc',
      'template' => 'culturefeed-uitpas-event-price-classes',
    ),
    'culturefeed_uitpas_event_uitpas_prices' => array(
      'variables' => array(
        'distribution_keys' => array(),
      ),
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
      'file' => 'theme.inc',
      'template' => 'culturefeed-uitpas-event-uitpas-prices',
    ),
    'culturefeed_uitpas_event_uitpas_price' => array(
      'variables' => array(
        'name' => '',
        'reduced_price' => array(),
        'price_classes' => array(),
      ),
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
      'file' => 'theme.inc',
      'template' => 'culturefeed-uitpas-event-uitpas-price',
    ),
    'culturefeed_uitpas_profile_section' => array(
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
      'template' => 'culturefeed-uitpas-profile-section',
    ),
    'culturefeed_uitpas_profile_section_register' => array(
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
      'template' => 'culturefeed-uitpas-profile-section-register',
    ),
    'culturefeed_uitpas_promotion' => array(
      'variables' => array('promotion' => NULL),
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
      'file' => 'theme.inc',
      'template' => 'culturefeed-uitpas-promotion',
    ),
    'culturefeed_uitpas_promotion_image' => array(
      'variables' => array(
        'path' => NULL,
        'maxheight' => 120,
        'maxwidth' => 120,
      ),
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
      'file' => 'theme.inc',
    ),
    'culturefeed_uitpas_promotions' => array(
      'variables' => array(
        'promotions' => array(),
        'promotions_total' => 0,
        'promotions_pager_element' => 0,
        'promotions_filter' => array(),
        'promotions_pager_min' => 0,
        'promotions_pager_max' => 0,
      ),
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
      'file' => 'theme.inc',
      'template' => 'culturefeed-uitpas-promotions',
    ),
    'culturefeed_uitpas_promotions_table' => array(
      'variables' => array(
        'title' => t('Promotions'),
        'promotions' => array(),
        'promotions_total' => 0,
        'promotions_pager_element' => 0,
        'items' => array(),
        'pager' => FALSE,
      ),
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
      'template' => 'culturefeed-uitpas-promotions-table',
      'file' => 'theme.inc',
    ),
    'culturefeed_uitpas_promotions_highlight' => array(
      'variables' => array('promotions' => array()),
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
      'file' => 'theme.inc',
      'template' => 'culturefeed-uitpas-promotions-highlight',
    ),
    'culturefeed_uitpas_profile_actions' => array(
      'variables' => array(
        'activities' => array(),
      ),
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
      'file' => 'theme.inc',
      'template' => 'culturefeed-uitpas-profile-actions',
    ),
    'culturefeed_uitpas_profile_promotions' => array(
      'variables' => array(
        'promotions' => array(),
        'promotions_total' => 0,
        'promotions_pager_min' => 0,
        'promotions_pager_max' => 0,
      ),
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
      'file' => 'theme.inc',
      'template' => 'culturefeed-uitpas-profile-promotions',
    ),
    'culturefeed_uitpas_profile_advantages' => array(
      'variables' => array(
        'advantages' => array(),
        'advantages_total' => 0,
      ),
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
      'file' => 'theme.inc',
      'template' => 'culturefeed-uitpas-profile-advantages',
    ),
    'culturefeed_uitpas_profile_details' => array(
      'variables' => array(
        'uitpas_user' => NULL,
        'passholder' => NULL,
      ),
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
      'file' => 'theme.inc',
      'template' => 'culturefeed-uitpas-profile-details',
    ),
    'culturefeed_uitpas_profile_details_form' => array(
      'render element' => 'form',
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
      'file' => 'theme.inc',
      'template' => 'culturefeed-uitpas-profile-details-form',
    ),
    'culturefeed_uitpas_profile_summary' => array(
      'variables' => array(
        'uitpas_user' => NULL,
        'passholder' => NULL,
        'advantages' => array(),
        'promotions' => array(),
        'upcoming_promotions' => array(),
      ),
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
      'file' => 'theme.inc',
      'template' => 'culturefeed-uitpas-profile-summary',
    ),
    'culturefeed_uitpas_recent_actions' => array(
      'variables' => array('actions' => array()),
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
      'file' => 'theme.inc',
      'template' => 'culturefeed-uitpas-recent-actions',
    ),
    'culturefeed_uitpas_register_where' => array(
      'variables' => array(
        'pos' => array(),
        'pos_total' => 0,
        'pos_pager_element' => 0,
        'filters' => array(),
        'actors' => array(),
      ),
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
      'file' => 'theme.inc',
      'template' => 'culturefeed-uitpas-register-where',
    ),
    'culturefeed_uitpas_filter_labels' => array(
      'render element' => 'element',
      'template' => 'culturefeed-uitpas-filter-labels',
      'path' => drupal_get_path('module', 'culturefeed_uitpas') . '/theme',
    )
  );
}

function culturefeed_uitpas_preprocess_culturefeed_actor(&$vars) {

  // Promotions.
  module_load_include('inc', 'culturefeed_uitpas', 'includes/event_details_advantages');
  $promotions = culturefeed_uitpas_event_details_advantages_get();
  $vars['uitpas_promotions'] = drupal_render($promotions);

}

/**
 * Preprocess function for culturefeed_agenda_event.
 */
function culturefeed_uitpas_preprocess_culturefeed_event(&$vars) {

  $event = culturefeed_uitpas_get_uitpas_event($vars['item']);

  if ($event) {

    // Price info.
    module_load_include('inc', 'culturefeed_uitpas', 'includes/event_price_info');
    $price_info = culturefeed_uitpas_get_price_info($event);

    if ($price_info['price_description']) {
      $vars['price_description'] = $price_info['price_description'];
    }

    if ($price_info['uitpas_prices']) {
      $vars['uitpas_prices'] = $price_info['uitpas_prices'];
    }

    // Promotions.
    module_load_include('inc', 'culturefeed_uitpas', 'includes/event_details_advantages');
    $promotions = culturefeed_uitpas_event_details_advantages_get();
    $vars['uitpas_promotions'] = drupal_render($promotions);

  }

}

/**
 * Preprocess function to add classes to radio input elements.
 */
function culturefeed_uitpas_preprocess_culturefeed_uitpas_filter_labels(&$variables) {
  $attributes = array();
  if (isset($variables['element']['#id'])) {
    $attributes['id'] = $variables['element']['#id'];
  }
  $attributes['class'] = 'form-radios';
  if (!empty($variables['element']['#attributes']['class'])) {
    $attributes['class'] .= ' ' . implode(' ', $variables['element']['#attributes']['class']);
  }
  if (isset($variables['element']['#attributes']['title'])) {
    $attributes['title'] = $variables['element']['#attributes']['title'];
  }
  foreach (element_children($variables['element']) as $child) {
    $variables['element'][$child]['#prefix'] = '<span class="' . drupal_html_class($variables['element'][$child]['#title']) . '">';
    $variables['element'][$child]['#suffix'] = '</span>';
    $variables['element'][$child]['#attributes']['data-counter'] = drupal_html_class($variables['element'][$child]['#title']);
    $rendered_child = drupal_render($variables['element'][$child]);

    $variables['element']['#children'] .= $rendered_child;
  }
  $variables['#attributes'] = $attributes;
}

function culturefeed_uitpas_preprocess_culturefeed_uitpas_event_price_classes(&$vars) {

  $table = array(
    '#theme' => 'table',
    '#rows' => array(),
  );

  foreach ($vars['price_classes_array'] as $price_class) {

    $table['#rows'][] = array(
      $price_class['name'],
      ($vars['reduced']) ? $price_class['reduced_price'] : $price_class['price'],
    );

  }
  $vars['price_classes_default_render'] = drupal_render($table);

}
