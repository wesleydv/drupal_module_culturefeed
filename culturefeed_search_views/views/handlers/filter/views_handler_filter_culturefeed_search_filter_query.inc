<?php
/**
 * @class
 * Handler class to handle filtering via the culturefeed search api by using a filter query.
 */
class views_handler_filter_culturefeed_search_filter_query extends views_handler_filter {

  // Field to search on.
  protected $search_field = '';

  /**
   * @see views_handler_filter::init()
   */
  function init(&$view, &$options) {
    parent::init($view, $options);
    $this->search_field = $this->real_field;
  }

  /**
   * Options form subform for exposed filter options.
   *
   * @see options_form()
   */
  function expose_form(&$form, &$form_state) {
    parent::expose_form($form, $form_state);
    unset($form['expose']['multiple']);
  }

  /**
   * @see views_handler_filter::value_form()
   */
  function value_form(&$form, &$form_state) {
    $form['value'] = array(
      '#type' => 'textfield',
      '#title' => t('Value'),
      '#size' => 30,
      '#default_value' => $this->value,
    );
  }

  /**
   * @see views_handler_filter::query()
   */
  function query() {

    $value = $this->getValue();
    $value = '"' . str_replace('"', '\"', $value) . '"';

    $this->query->add_where($this->options['group'], 'fq', $this->search_field . ':' . $value);
  }

  /**
   * Get the value to query.
   */
  function getValue() {
    return is_array($this->value) ? $this->value[0] : $this->value;
  }

}