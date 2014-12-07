<?php

/**
 * @file
 * Contains the theming functions for the culturefeed date control.
 */

/**
 * Theme the hybrid table.
 *
 * @param array $variables
 *   The variables.
 *
 * @return string
 *   The output.
 */
function theme_culturefeed_date_control_hybrid_table(array &$variables) {

  $form = $variables['form'];

  $table = array(
    'attributes' => array(
      'class' => array(
        'date-control-table',
        'date-control-hybrid-table',
      ),
    ),
    'rows' => array(),
  );

  $cells = array();
  $cells[] = drupal_render($form['start_date']);
  $cells[] = drupal_render($form['start_time']);
  $cells[] = drupal_render($form['add_time']) . drupal_render($form['add_end_date']);
  $table['rows'][] = $cells;

  $output = theme('table', $table);
  $output .= drupal_render_children($form);
  return $output;

}

/**
 * Theme the timestamps table.
 *
 * @param array $variables
 *   The variables.
 *
 * @return string
 *   The output.
 */
function theme_culturefeed_date_control_opening_times_table(array &$variables) {

  $form = $variables['form'];

  $header = array(t('open'), t('from'), t('to'));
  $table = array(
    'attributes' => array(
      'class' => array(
        'date-control-table',
        'date-control-opening-times-table',
      ),
    ),
    'header' => $header,
    'rows' => array(),
  );

  foreach (element_children($form) as $element) {

    $cells = array();
    $cells[] = $form[$element]['#title'];
    $cells[] = array(
      'data' => drupal_render($form[$element][0]['open_from']),
      'class' => 'culturefeed-date-control-opening-times-complete',
    );
    $cells[] = array(
      'data' => drupal_render($form[$element][0]['open_till']),
      'class' => 'culturefeed-date-control-opening-times-complete',
    );
    $table['rows'][] = $cells;

  }

  $output = theme('table', $table);
  return $output;

}

/**
 * Theme the period table.
 *
 * @param array $variables
 *   The variables.
 *
 * @return string
 *   The output.
 */
function theme_culturefeed_date_control_period_table(array &$variables) {

  $form = $variables['form'];

  $table = array(
    'attributes' => array(
      'class' => array(
        'date-control-table',
        'date-control-period-table',
      ),
    ),
    'rows' => array(),
  );

  $cells = array(drupal_render($form['start_date']));
  if ($form['add_end']['#access']) {
    $cells[] = drupal_render($form['add_end']);
  }
  if ($form['end_date']['#access']) {
    $cells[] = drupal_render($form['end_date']);
  }
  if ($form['remove_end']['#access']) {
    $cells[] = drupal_render($form['remove_end']);
  }

  $table['rows'][] = $cells;
  $output = theme('table', $table);
  return $output;

}

/**
 * Theme the timestamps table.
 *
 * @param array $variables
 *   The variables.
 *
 * @return string
 *   The output.
 */
function theme_culturefeed_date_control_timestamps_table(array &$variables) {

  $form = $variables['form'];

  $table = array(
    'attributes' => array(
      'class' => array(
        'date-control-table',
        'date-control-timestamps-table',
      ),
    ),
    'rows' => array(),
  );

  foreach (element_children($form['stamps']) as $element) {

    if ($element !== 'timestamps_add_stamp') {

      $cells = array();
      // Date and time link is always present.
      $cell_count = 0;

      if ($form['stamps'][$element]['remove_stamp']['#access']) {
        $cells[] = drupal_render($form['stamps'][$element]['remove_stamp']);
        $cell_count++;
      }

      $cells[] = drupal_render($form['stamps'][$element]['date']);
      $cell_count++;

      if ($form['stamps'][$element]['add_start']['#access']) {
        $cells[] = drupal_render($form['stamps'][$element]['add_start']);
        $cell_count++;
      }
      elseif ($form['stamps'][$element]['start_time']['#access']) {
        $cells[] = drupal_render($form['stamps'][$element]['start_time']);
        $cell_count++;
      }

      // Remove start and add end are rendered together.
      $cell = '';
      if ($form['stamps'][$element]['remove_start']['#access']) {
        $cell .= drupal_render($form['stamps'][$element]['remove_start']);
      }
      if ($form['stamps'][$element]['add_end']['#access']) {
        $cell .= drupal_render($form['stamps'][$element]['add_end']);
      }
      if ($cell) {
        $cells[] = $cell;
        $cell_count++;
      }

      if ($form['stamps'][$element]['end_time']['#access']) {
        $cells[] = drupal_render($form['stamps'][$element]['end_time']);
        $cell_count++;
      }
      if ($form['stamps'][$element]['remove_end']['#access']) {
        $cells[] = drupal_render($form['stamps'][$element]['remove_end']);
        $cell_count++;
      }

      while ($form['#cell_count'] - $cell_count > 0) {
        $cells[] = '';
        $cell_count++;
      }

      $table['rows'][] = $cells;

    }

  }

  $output = theme('table', $table);
  $output .= drupal_render_children($form);
  return $output;

}
