<?php

/**
 * A handler to provide proper displays for the location of a cdb item.
 */
class views_handler_field_cdb_item_location extends views_handler_field {

  /**
   * @see views_handler_field::option_definition()
   */
  function option_definition() {

    $options = parent::option_definition();
    $options['show'] = array('default' => array('city' => 'city'));

    return $options;

  }

  /**
   * @see views_handler_field::options_form()
   */
  function options_form(&$form, &$form_state) {

    $form['show'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Show'),
      '#default_value' => isset($this->options['show']) ? $this->options['show'] : array('title'),
      '#options' => array(
        'title' => t('Title'),
        'city' => t('City'),
        'address' => t('Address'),
      ),
      '#required' => TRUE,
    );

    parent::options_form($form, $form_state);

  }

  /**
   * @see views_handler_field::render()
   */
  function render($extended_entity) {

    $entity_type = $extended_entity->getType();
    $cdb_item = $extended_entity->getEntity();
    $location = array();

    switch ($entity_type) {

      // Event: show location.
      case 'event':
        $location = culturefeed_agenda_get_location_of_event($extended_entity->getEntity());
        break;

      // Production = show locations of related events.
      case 'production':

        $relations = $cdb_item->getRelations();
        $total_relations = count($relations);
        // No event data.
        if ($total_relations == 0) {
          return;
        }
        // Multiple events. No fixed location.
        elseif ($total_relations > 1) {
          $location['title'] = 'meerdere locaties';
        }
        // 1 event. Use events location.
        else {

          try {
            $event = culturefeed_agenda_event_load(current($relations)->getCdbid());
            $location = culturefeed_agenda_get_location_of_event($event->getEntity());
          }
          catch (Exception $e) {
            watchdog_exception('culturefeed_search_views', $e);
          }
        }

        break;

      // Actor = show the contact info address.
      case 'actor':

      if ($cdb_item->getContactInfo()) {

          $contact_info = $cdb_item->getContactInfo();
          $addresses = $contact_info->getAddresses();

          if ($addresses) {

            $location['title'] = $addresses[0]->getLabel();
            $physical_address = $addresses[0]->getPhysicalAddress();
            if ($physical_address) {
              $location['city'] = check_plain($physical_address->getCity());
              $location['street'] = check_plain($physical_address->getStreet() . ' ' . $physical_address->getHouseNumber());
              $location['zip'] = check_plain($physical_address->getZip());
            }
          }
        }

        break;

      case 'page':
        $address = $cdb_item->getAddress();
        if (!empty($address)) {

          if ($address->getStreet()) {
            $location['street'] = check_plain($address->getStreet() . ' ' . $address->getHouseNumber());
          }

          $location['city'] = check_plain($address->getCity());
          $location['zip'] = check_plain($address->getZip());

        }
        break;
    }

    $show = $this->options['show'];

    $output = array();
    if (!empty($show['title']) && !empty($location['title'])) {
      $output[] = $location['title'];
    }

    if (!empty($show['address']) && !empty($location['street'])) {
      $output[] = $location['street'] . ' ' . $location['zip'] . ' ' . $location['city'];
    }
    elseif (!empty($show['city']) && !empty($location['city'])) {
      $output[] = $location['city'];
    }

    return implode(' ', $output);

  }

}
