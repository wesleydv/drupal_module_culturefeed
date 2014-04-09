<?php

/**
 * A handler to provide proper displays for the tagline of a cdb item.
 */
class views_handler_field_cdb_item_tagline extends views_handler_field {

  /**
   * @see views_handler_field::render()
   */
  function render($extended_entity) {

    if ($extended_entity->getType() == 'page') {
      return check_plain($extended_entity->getEntity()->getTagline());
    }
  }

}
