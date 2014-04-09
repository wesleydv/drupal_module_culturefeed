<?php

/**
 * @class
 * Handler class for sorting on distance on search api.
 */
class views_handler_sort_culturefeed_search_distance extends views_handler_sort_culturefeed_search_base {

  protected $sort_field = '';

  function option_definition() {

    $options = parent::option_definition();

    $options['direction'] = array('default' => 'ASC');
    $options['latitude'] = array('default' => '');
    $options['longitude'] = array('default' => '');

    return $options;
  }

  /**
   * Basic options for all sort criteria
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['latitude'] = array(
      '#title' => t('Latitude'),
      '#type' => 'textfield',
      '#description' => t('Latitude of the point to use for the distance calculation'),
      '#default_value' => $this->options['latitude'],
    );

    $form['longitude'] = array(
      '#title' => t('Longitude'),
      '#type' => 'textfield',
      '#description' => t('Longitude of the point to use for the distance calculation'),
      '#default_value' => $this->options['longitude'],
    );
  }

  /**
   * @see views_handler_sort::admin_summary()
   */
  function admin_summary() {
    return $this->options['order'] . ' - ' . $this->options['latitude'] . ', ' . $this->options['longitude'];
  }

  /**
   * @see views_handler_sort::query()
   */
  function query() {

    $parameter = new \CultuurNet\Search\Parameter\Parameter('pt', $this->options['latitude'] . ',' . $this->options['longitude']);
    $this->query->add_parameter($parameter);

    $parameter = new \CultuurNet\Search\Parameter\Parameter('sfield', 'physical_gis');
    $this->query->add_parameter($parameter);

    $parameter = new \CultuurNet\Search\Parameter\Sort('geodist()', $this->options['order']);
    $this->query->add_parameter($parameter);
  }

}
