<?php

/**
 * A handler to provide proper displays for the categories of a cdb item.
 */
class views_handler_field_cdb_item_categories extends views_handler_field {

  /**
   * @see views_handler_field::render()
   */
  function render($extended_entity) {

    if ($extended_entity->getType() == 'page') {

      $categories = $extended_entity->getEntity()->getCategories();
      $translations = culturefeed_search_term_translations($categories, TRUE);

      $labels = array();
      foreach ($translations as $translation) {
        if (isset($translation[culturefeed_search_get_preferred_language()])) {
          $labels[] = $translation[culturefeed_search_get_preferred_language()];
        }
        else {
          $labels[] = $translation[LANGUAGE_NONE];
        }
      }

      return check_plain(implode(', ', $labels));
    }
  }

}
