<?php

/**
 * @file
 * Contains the functions for the culturefeed date control form element.
 */

/**
 * Pre renders the culturefeed date control.
 *
 * @param array $element
 *   The element.
 *
 * @return array $element
 *   The element.
 */
function culturefeed_date_control_date_control_pre_render(array $element) {

  $value = $element['#value'];

  if ($value['date_control']['type'] == 'hybrid') {

    $element['date_control']['opening_times']['#access'] = FALSE;
    $element['date_control']['period']['#access'] = FALSE;
    $element['date_control']['permanent']['#access'] = FALSE;
    $element['date_control']['timestamps']['#access'] = FALSE;

  }

  elseif ($value['date_control']['type'] == 'period') {

    $element['date_control']['hybrid']['#access'] = FALSE;
    $element['date_control']['permanent']['#access'] = FALSE;
    $element['date_control']['timestamps']['#access'] = FALSE;

  }

  elseif ($value['date_control']['type'] == 'permanent') {

    $element['date_control']['hybrid']['#access'] = FALSE;
    $element['date_control']['period']['#access'] = FALSE;
    $element['date_control']['timestamps']['#access'] = FALSE;

  }

  elseif ($value['date_control']['type'] == 'timestamps') {

    $element['date_control']['hybrid']['#access'] = FALSE;
    $element['date_control']['opening_times']['#access'] = FALSE;
    $element['date_control']['period']['#access'] = FALSE;
    $element['date_control']['permanent']['#access'] = FALSE;

  }

  return $element;

}

/**
 * Returns the culturefeed date control element.
 *
 * @param array $element
 *   The element.
 * @param array $form_state
 *   The form state.
 * @param array $form
 *   The form.
 *
 * @return array
 *   The processed element.
 */
function culturefeed_date_control_date_control_process(array $element, array &$form_state, array $form) {

  $element['#prefix'] = "<div id=\"" . $element['#id'] . "-ajax-wrapper\">";
  $element['#suffix'] = "</div>";

  $element['date_control'] = array(
    '#type' => 'fieldset',
    '#title' => (isset($element['#title'])) ? $element['#title'] : t('Dates'),
  );

  // Type.
  $element['date_control']['type'] = array(
    '#type' => 'hidden',
    '#value' => $element['#value']['date_control']['type'],
  );

  // Hybrid.
  $element['date_control']['hybrid'] = array(
    '#access' => TRUE,
    '#date_control' => $element,
    '#popup_date_format' => 'd-m-Y',
    '#popup_date_increment' => 1,
    '#select_time_format' => 'H:i',
    '#select_time_increment' => 30,
    '#type' => 'culturefeed_date_control_hybrid',
  );

  // Timestamps.
  $element['date_control']['timestamps'] = array(
    '#access' => TRUE,
    '#date_control' => $element,
    '#default_value' => $element['#default_value']['timestamps'],
    '#popup_date_format' => 'd-m-Y',
    '#popup_date_increment' => 1,
    '#select_time_format' => 'H:i',
    '#select_time_increment' => 30,
    '#type' => 'culturefeed_date_control_timestamps',
  );

  // Period.
  $element['date_control']['period'] = array(
    '#access' => TRUE,
    '#date_control' => $element,
    '#default_value' => $element['#default_value']['period'],
    '#popup_date_format' => 'd-m-Y',
    '#popup_date_increment' => 1,
    '#type' => 'culturefeed_date_control_period',
  );

  // Permanent.
  $element['date_control']['permanent'] = array(
    '#access' => TRUE,
    '#ajax' => array(
      'effect' => 'none',
      'path' => 'culturefeed_elements/ajax/' . implode('/', $element['#array_parents']),
      'progress' => array('type' => 'throbber'),
      'wrapper' => $element['#id'] . '-ajax-wrapper',
    ),
    '#value' => isset($element['#value']['date_control']['permanent']) ? $element['#value']['date_control']['permanent'] : 0,
    '#title' => t('Permanent'),
    '#type' => 'checkbox',
  );

  // Opening times.
  $element['date_control']['opening_times'] = array(
    '#access' => TRUE,
    '#allowed_days' => $element['#allowed_days'],
    '#date_control' => $element,
    '#default_value' => $element['#default_value']['opening_times'],
    '#type' => 'culturefeed_date_control_opening_times',
  );

  $element['#attached'] = array(
    'css' => array(
      drupal_get_path('module', 'culturefeed_date_control') . '/css/culturefeed_date_control.css',
    ),
  );

  return $element;

}

/**
 * Submit handler for the ajax buttons.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function culturefeed_date_control_date_control_submit(array $form, array &$form_state) {

  $form_state['rebuild'] = TRUE;

}

/**
 * Validate and alter the culturefeed date control form values.
 *
 * This is where the element switching is set, based on values.
 *
 * @param array $element
 *   The element.
 * @param array $form_state
 *   The form state.
 */
function culturefeed_date_control_date_control_validate(array $element, array &$form_state) {

  $triggering_element = (isset($form_state['triggering_element'])) ? $form_state['triggering_element'] : '';
  $triggering_parent = array_pop($triggering_element['#parents']);
  // Use form_state instead of element as individual sub elements have changes
  // that won't be reflected in element.
  $values = drupal_array_get_nested_value($form_state['input'], $element['#parents']);
  $date_control = $values['date_control'];

  if (culturefeed_date_control_check_trigger_element($triggering_element, $element)) {

    $type = $date_control['type'];

    // Hybrid.
    if ($date_control['type'] == 'hybrid') {

      // Period.
      if ($triggering_parent == 'end_date') {

        $type = 'period';
        $date_control['period'] = array('start_date' => '');
        if (isset($date_control['hybrid']['start_date'])) {
          $date_control['period']['start_date'] = $date_control['hybrid']['start_date'];
        }
        if (isset($date_control['hybrid']['end_date'])) {
          $date_control['period']['end_date'] = $date_control['hybrid']['end_date'];
        }

      }

      // Permanent.
      if ($triggering_parent == 'permanent') {

        $type = 'permanent';
        $date_control['permanent'] = 1;

      }

      // Timestamps.
      if ($triggering_parent == 'add_date' || $triggering_parent == 'hour' || $triggering_parent == 'minute') {

        $type = 'timestamps';
        $date_control['timestamps']['stamps'] = array(
          array('date' => ''),
        );
        if (isset($date_control['hybrid']['start_date'])) {
          $date_control['timestamps']['stamps'][0]['date'] = $date_control['hybrid']['start_date'];
        }
        if (isset($date_control['hybrid']['start_time'])) {
          $date_control['timestamps']['stamps'][0]['start_time'] = $date_control['hybrid']['start_time'];
        }
        if (isset($date_control['hybrid']['end_time'])) {
          $date_control['timestamps']['stamps'][0]['end_time'] = $date_control['hybrid']['end_time'];
        }
        if ($triggering_parent == 'add_date') {
          $date_control['timestamps']['stamps'][] = array('date' => '');
        }

      }

    }

    // Period.
    if ($date_control['type'] == 'period') {

      if ($triggering_parent == 'remove_end') {

        $type = 'hybrid';
        // Pass over any set values.
        $date_control['hybrid'] = array(
          'start_date' => isset($date_control['period']['start_date']) ? $date_control['period']['start_date'] : '',
        );

      }

    }

    // Permanent.
    if ($date_control['type'] == 'permanent') {

      if ($triggering_parent == 'permanent') {

        $type = 'hybrid';

      }

    }

    // Timestamps.
    if ($date_control['type'] == 'timestamps') {

      if (
        (($triggering_parent == 'remove_stamp' && !isset($date_control['timestamps']['stamps'][0]['end_time'])) ||
          $triggering_parent == 'remove_end')  && count($date_control['timestamps']['stamps']) == 1
      ) {

        $type = 'hybrid';
        $date_control['hybrid'] = array('start_date' => '');
        if (isset($date_control['timestamps']['stamps'][0]['date'])) {
          $date_control['hybrid']['start_date'] = $date_control['timestamps']['stamps'][0]['date'];
        }
        if (isset($date_control['timestamps']['stamps'][0]['start_time'])) {
          $date_control['hybrid']['start_time'] = $date_control['timestamps']['stamps'][0]['start_time'];
        }

      }

    }

    $date_control['type'] = $type;
    $element['#parents'][] = 'date_control';

    drupal_array_set_nested_value($form_state['input'], $element['#parents'], $date_control);

  }

}

/**
 * Value callback for the date control element.
 *
 * @param array $element
 *   The element.
 * @param mixed $input
 *   The input.
 * @param array $form_state
 *   The form state.
 *
 * @return mixed
 *   The value.
 */
function culturefeed_date_control_date_control_value_callback(array &$element, $input, array $form_state) {

  if ($input) {
    return $input;
  }
  else {

    // Default value or an empty value.
    if (isset($element['#default_value'])) {

      $date_control = array(
        'hybrid' => array(),
        'opening_times' => array(),
        'period' => array(),
        'timestamps' => array(),
      );

      // Timestamps.
      if (count($element['#default_value']['timestamps'])) {

        $date_control['type'] = 'timestamps';
        $date_control['timestamps'] = $element['#default_value']['timestamps'];

      }

      // Period.
      elseif ($element['#default_value']['period']['start_date'] && $element['#default_value']['period']['end_date']) {

        $date_control['type'] = 'period';
        $date_control['period'] = $element['#default_value']['period'];

      }

      // Permanent.
      elseif ($element['#default_value']['permanent']) {

        $date_control['type'] = 'permanent';
        $date_control['permanent'] = $element['#default_value']['permanent'];

      }

      else {
        $date_control['type'] = 'hybrid';
      }

      // Opening times don't set type, they go with period or permanent.
      if ($element['#default_value']['opening_times']) {

        $date_control['opening_times'] = $element['#default_value']['opening_times'];

      }

      return array('date_control' => $date_control);

    }

    else {

      return array(
        'date_control' => array(
          'type' => 'hybrid',
          'hybrid' => array(),
          'opening_times' => array(),
          'period' => array(),
          'timestamps' => array(),
        ),
      );

    }

  }

}