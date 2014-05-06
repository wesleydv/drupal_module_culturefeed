<?php
/**
 * @file
 * Admin settings for culturefeed_agenda.
 */

/**
 * General settings for agenda.
 */
function culturefeed_agenda_admin_settings_form($form_state) {

  /*$page_info = culturefeed_agenda_culturefeed_search_page_info();
  $agenda_page = current($page_info);

  $form = array();
  $form['culturefeed-agenda-default-sort'] = array(
    '#title' => t('Default sorting for agenda'),
    '#type' => 'select',
    '#options' => $agenda_page['sort_options'],
    '#default_value' => $agenda_page['sort_default'],
  );*/
  
  global $num_rows;
  global $options;
  
  $num_rows = !empty($num_rows) ? $num_rows : 3;
  
  $options = array(
    'relevancy' => t('Relevance'),
    'date' => t('Date'),
    'recommend_count' => t('Recommended'),
    'comment_count' => t('Reactions'),
    'distance' => t('Distance'),
  );
  
  $form['culturefeed-agenda-sort-advanced'] = array(
    '#tree' => TRUE,
    '#theme' => 'culturefeed_agenda_admin_settings_form',
    '#prefix' => '<div id="culturefeed-agenda-sort-advanced-form-wrapper">',
    '#suffix' => '</div>',
    '#type' => 'tableselect',
  );

  for ($i = 1; $i <= $num_rows; $i++) {
    $form['culturefeed-agenda-sort-advanced'][$i] = array(
      'name' => array(
        '#markup' => 'culturefeed-agenda-sort-advanced-form' . $i,
      ),
      
      'default' => array(
        '#type' => 'radio',
        '#title' => t('default'),
        '#title_display' => 'invisible',
        '#default_value' => 0,
      ),
      
      'enabled' => array(
        '#type' => 'checkbox',
        '#title' => t('enabled'),
        '#title_display' => 'invisible',
        '#default_value' => 1,
      ),

      'label' => array(
        '#type' => 'textfield',
        '#title' => t('label'),
        '#title_display' => 'invisible',
        '#size' => 20,
        '#maxlength' => 255,
      ),
      
      'value' => array(
        '#type' => 'select',
        '#title' => t('value'),
        '#title_display' => 'invisible',
        '#options' => $options,
      ),
      
      'sort' => array(
        '#type' => 'textfield',
        '#title' => t('sort'),
        '#title_display' => 'invisible',
        '#size' => 20,
        '#maxlength' => 255,
      ),
      
      'weight' => array(
        '#type' => 'weight',
        '#title' => t('Weight'),
        '#title_display' => 'invisible',
        '#delta' => 10,
        '#title_display' => 'invisible',
      ),
      
      'delete' => array(
        '#type' => 'link',
        '#title' => t('Delete'),
        '#href' => '#',
        '#value' => t('Delete'),
        '#ajax' => array(
          'callback' => 'ajax_culturefeed_agenda_delete_row_callback',
          'wrapper' => 'culturefeed-agenda-sort-advanced-form' . $i,
        ),
      ),
    );
  }

  // Now we add our submit button, for submitting the form results.
  $form['add_row'] = array(
    '#type' => 'button',
    '#name' => 'new_row',
    '#value' => t('Add row'),
    '#ajax' => array(
      'callback' => 'ajax_culturefeed_agenda_sort_callback',
      'wrapper' => 'culturefeed-agenda-sort-advanced-form-wrapper',
    ),
  );

  return system_settings_form($form);
}

function ajax_culturefeed_agenda_delete_row_callback(&$form, &$form_state) {
  global $num_rows;
  $num_rows--;
  
  return $form['culturefeed-agenda-sort-advanced'];
}

function ajax_culturefeed_agenda_sort_callback(&$form, &$form_state) {
  
  global $num_rows;

  if ($form_state['triggering_element']['#name'] == 'new_row') {
    $num_rows++;

    return $form['culturefeed-agenda-sort-advanced'];
  }
}

function theme_culturefeed_agenda_admin_settings_form($form) {
  $form = current($form);
  $header = array(t('Default'), t('Enabled'), t('Label'), t('Value'), t('Sort'), t('Weight'), t('Delete'));
  
  $rows = array();

  foreach (element_children($form) as $id) {
    $form[$id]['weight']['#attributes']['class'] = array('culturefeed-agenda-sort-advanced-weight');
    $rows[] = array(
      'data' => array(
        drupal_render($form[$id]['default']),
        drupal_render($form[$id]['enabled']),
        drupal_render($form[$id]['label']),
        drupal_render($form[$id]['value']),
        drupal_render($form[$id]['sort']),
        drupal_render($form[$id]['weight']),
        drupal_render($form[$id]['delete']),
      ),
      'class' => array('draggable'),
    );
  }

  $table_id = 'culturefeed-agenda-sort-advanced-table';

  // We can render our tabledrag table for output.
  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => $table_id),
  ));

  // We now call the drupal_add_tabledrag() function in order to add the
  // tabledrag.js goodness onto our page.
  drupal_add_tabledrag($table_id, 'order', 'sibling', 'culturefeed-agenda-sort-advanced-weight');

  return $output;
}
