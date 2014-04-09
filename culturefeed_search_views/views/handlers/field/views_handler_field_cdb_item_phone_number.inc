<?php

/**
 * A handler to provide proper displays for telephone numbers of cdb items.
 */
class views_handler_field_cdb_item_phone_number extends views_handler_field {

  /**
   * @see views_handler_field::render()
   */
  function render($extended_entity) {

    if ($extended_entity->getType() == 'page') {
      return $extended_entity->getEntity()->getTelephone();
    }
  }

}
