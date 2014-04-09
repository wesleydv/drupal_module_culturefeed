<?php

/**
 * A handler to provide proper displays for cdbids.
 */
class views_handler_field_cdb_item_id extends views_handler_field {

  /**
   * @see views_handler_field::render()
   */
  function render($extended_entity) {
    return $extended_entity->getId();
  }

}
