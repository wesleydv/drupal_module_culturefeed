<?php

/**
 * A handler to provide proper displays for the links of page.
 */
class views_handler_field_cdb_item_page_link extends views_handler_field {

  /**
   * @see views_handler_field::option_definition()
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['url'] = array('default' => FALSE);

    return $options;
  }

  /**
   * @see views_handler_field::options_form()
   */
  function options_form(&$form, &$form_state) {

    $form['url'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display as link'),
      '#default_value' => isset($this->options['url']) ? $this->options['url'] : FALSE,
    );

    parent::options_form($form, $form_state);
  }

  /**
   * @see views_handler_field::render()
   */
  function render($extended_entity) {

    if ($extended_entity->getType() != 'page') {
      return;
    }

    $links = $extended_entity->getEntity()->getLinks();

    // If type doesn't exist, try to show website.
    $key = isset($links[$this->real_field]) ? $this->real_field : 'linkWebsite';

    if (!isset($links[$key])) {
      return;
    }

    $link = $links[$key];
    if (isset($this->options['url']) && $this->options['url']) {
      $link = l($link, $link);
    }

    return $link;
  }

}
