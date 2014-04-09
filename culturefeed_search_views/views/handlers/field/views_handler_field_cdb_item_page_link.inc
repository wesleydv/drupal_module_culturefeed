<?php

/**
 * A handler to provide proper displays for the links of page.
 */
class views_handler_field_cdb_item_page_link extends views_handler_field {

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

    return isset($links[$key]) ? $links[$key] : NULL;
  }

}
