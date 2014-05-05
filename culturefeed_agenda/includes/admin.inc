<?php
/**
 * @file
 * Admin settings for culturefeed_agenda.
 */

/**
 * General settings for agenda.
 */
function culturefeed_agenda_admin_settings_form() {

  /*$page_info = culturefeed_agenda_culturefeed_search_page_info();
  $agenda_page = current($page_info);

  $form = array();
  $form['culturefeed-agenda-default-sort'] = array(
    '#title' => t('Default sorting for agenda'),
    '#type' => 'select',
    '#options' => $agenda_page['sort_options'],
    '#default_value' => $agenda_page['sort_default'],
  );*/
  
  $form['culturefeed-agenda-sort-advanced'] = array(
    '#tree' => TRUE,
    '#theme' => 'culturefeed_agenda_admin_settings_form',
  );
  
    //$form['culturefeed-agenda-sort-advanced'][$item->id] = array(
    $form['culturefeed-agenda-sort-advanced']['date'] = array(
      'name' => array(
        '#markup' => 'date',
      ),
      
      'default' => array(
        '#type' => 'radio',
        '#title' => t('default'),
        '#default_value' => 0,
      ),
      
      'enabled' => array(
        '#type' => 'checkbox',
        '#title' => t('enabled'),
        '#default_value' => 1,
      ),

      'label' => array(
        '#type' => 'textfield',
        '#title' => t('label'),
        '#size' => 20,
        '#maxlength' => 255,
      ),
      
      'value' => array(
        '#type' => 'select',
        '#title' => t('value'),
        '#default_value' => 'date',
        '#options' => array(
          'relevancy' => t('Relevance'),
          'date' => t('Date'),
          'recommend_count' => t('Recommended'),
          'comment_count' => t('Reactions'),
        ),
      ),
      
      'sort' => array(
        '#type' => 'textfield',
        '#title' => t('sort'),
        '#size' => 20,
        '#maxlength' => 255,
      ),
      
      'weight' => array(
        '#type' => 'weight',
        '#title' => t('Weight'),
        //'#default_value' => $item->weight,
        '#delta' => 10,
        '#title_display' => 'invisible',
      ),
    );
    
    $form['culturefeed-agenda-sort-advanced']['relevancy'] = array(
      'name' => array(
        '#markup' => 'relevancy',
      ),
      
      'default' => array(
        '#type' => 'radio',
        '#title' => t('default'),
        '#default_value' => 0,
      ),
      
      'enabled' => array(
        '#type' => 'checkbox',
        '#title' => t('enabled'),
        '#default_value' => 1,
      ),

      'label' => array(
        '#type' => 'textfield',
        '#title' => t('label'),
        '#size' => 20,
        '#maxlength' => 255,
      ),
      
      'value' => array(
        '#type' => 'select',
        '#title' => t('value'),
        '#default_value' => 'relevancy',
        '#options' => array(
          'relevancy' => t('Relevance'),
          'date' => t('Date'),
          'recommend_count' => t('Recommended'),
          'comment_count' => t('Reactions'),
        ),
      ),
      
      'sort' => array(
        '#type' => 'textfield',
        '#title' => t('sort'),
        '#size' => 20,
        '#maxlength' => 255,
      ),
      
      'weight' => array(
        '#type' => 'weight',
        '#title' => t('Weight'),
        //'#default_value' => $item->weight,
        '#delta' => 10,
        '#title_display' => 'invisible',
      ),
    );
    
    $form['culturefeed-agenda-sort-advanced']['recommended'] = array(
      'name' => array(
        '#markup' => 'recommended',
      ),
      
      'default' => array(
        '#type' => 'radio',
        '#title' => t('default'),
        '#default_value' => 0,
      ),
      
      'enabled' => array(
        '#type' => 'checkbox',
        '#title' => t('enabled'),
        '#default_value' => 1,
      ),

      'label' => array(
        '#type' => 'textfield',
        '#title' => t('label'),
        '#size' => 20,
        '#maxlength' => 255,
      ),
      
      'value' => array(
        '#type' => 'select',
        '#title' => t('value'),
        '#default_value' => 'recommend_count',
        '#options' => array(
          'relevancy' => t('Relevance'),
          'date' => t('Date'),
          'recommend_count' => t('Recommended'),
          'comment_count' => t('Reactions'),
        ),
      ),
      
      'sort' => array(
        '#type' => 'textfield',
        '#title' => t('sort'),
        '#size' => 20,
        '#maxlength' => 255,
      ),
      
      'weight' => array(
        '#type' => 'weight',
        '#title' => t('Weight'),
        //'#default_value' => $item->weight,
        '#delta' => 10,
        '#title_display' => 'invisible',
      ),
    );

  // Now we add our submit button, for submitting the form results.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save'));

  //return system_settings_form($form);
  return $form;
}

function theme_culturefeed_agenda_admin_settings_form($variables) {
  dsm($variables);
  
  $form = $variables['form'];
  var_dump($form);
  $rows = array();
  
  foreach (element_children($form) as $id) {

    $form['culturefeed-agenda-sort-advanced'][$id]['weight']['#attributes']['class'] = array('culturefeed-agenda-sort-advanced-weight');

    $rows[] = array(
      'data' => array(
        drupal_render($form['culturefeed-agenda-sort-advanced'][$id]['default']),
        drupal_render($form['culturefeed-agenda-sort-advanced'][$id]['enabled']),
        drupal_render($form['culturefeed-agenda-sort-advanced'][$id]['label']),
        drupal_render($form['culturefeed-agenda-sort-advanced'][$id]['value']),
        drupal_render($form['culturefeed-agenda-sort-advanced'][$id]['sort']),
        drupal_render($form['culturefeed-agenda-sort-advanced'][$id]['weight']),
      ),
      'class' => array('draggable'),
    );
  }
  
  $header = array(t('Default'), t('Enabled'), t('Label'), t('Value'), t('Sort'), t('Weight'));

  $table_id = 'culturefeed-agenda-sort-advanced-table';

  // We can render our tabledrag table for output.
  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => $table_id),
  ));

  // And then render any remaining form elements (such as our submit button).
  $output .= drupal_render_children($form);

  // We now call the drupal_add_tabledrag() function in order to add the
  // tabledrag.js goodness onto our page.
  drupal_add_tabledrag($table_id, 'order', 'sibling', 'culturefeed-agenda-sort-advanced-weight');

  return $output;
}
