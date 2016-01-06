<?php

/**
 * @file
 * Helper functions for UiTPAS event prices.
 */

/**
 * Get the uitpas price info for an uitpas event.
 *
 * @param CultureFeed_Uitpas_Event_CultureEvent $event
 *   The event.
 *
 * @return array
 *   The price info.
 */
function culturefeed_uitpas_get_price_info(CultureFeed_Uitpas_Event_CultureEvent $event) {

  $price_info = array(
    'price_description' => '',
    'uitpas_prices' => '',
  );

  $default_price_classes = array();
  $default_price_classes_array = array();

  $distribution_keys = array();
  $distribution_keys_default_render = array();

  foreach ($event->cardSystems as $card_system) {

    foreach ($card_system->distributionKeys as $distributionKey) {

      $price_classes = array();
      $price_classes_array = array();
      foreach ($distributionKey->priceClasses as $priceClass) {

        $price_classes[] = $priceClass;
        $price_classes_array[] = array(
          'name' => $priceClass->name,
          'price' => number_format($priceClass->price, 2, ',', '.'),
          'reduced_price' => number_format($priceClass->price - $priceClass->tariff, 2, ',', '.'),
        );

      }

      if (count($price_classes)) {

        // For the base price info the first available distribution keys of
        // the first available card system are used.
        if (!count($default_price_classes)) {
          $default_price_classes = $price_classes;
          $default_price_classes_array = $price_classes_array;
        }

        $distribution_key = array(
          'name' => $distributionKey->name,
          'default_price' => $price_classes_array[0]['price'],
          'reduced_default_price' => $price_classes_array[0]['reduced_price'],
          'price_classes' => $price_classes,
          'price_classes_array' => $price_classes_array,
        );

        $price_classes = theme('culturefeed_uitpas_event_price_classes', array(
          'price_classes' => $distribution_key['price_classes'],
          'price_classes_array' => $distribution_key['price_classes_array'],
          'reduced' => TRUE,
        ));

        $distribution_keys_default_render[] = theme('culturefeed_uitpas_event_uitpas_price', array(
          '#theme' => 'culturefeed_uitpas_event_uitpas_price',
          '#name' => $distribution_key['name'],
          '#reduced_price' => $distribution_key['reduced_default_price'],
          '#price_classes' => $price_classes,
        ));

        $distribution_keys[] = $distribution_key;

      }

    }

  }

  if (count($default_price_classes)) {

    $price_info['price_description'] = theme('culturefeed_uitpas_event_price_classes', array(
      'price_classes' => $default_price_classes,
      'price_classes_array' => $default_price_classes_array,
    ));

  }

  if (count($distribution_keys)) {

    $price_info['uitpas_prices'] = theme('culturefeed_uitpas_event_uitpas_prices', array(
      'distribution_keys' => $distribution_keys,
      'distribution_keys_default_render' => $distribution_keys_default_render,
    ));

  }

  return $price_info;

}
