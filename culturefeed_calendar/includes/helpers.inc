<?php

/**
 * Helper functions for calendar.
 */

/**
 * Get the users activities.
 */
function culturefeed_calendar_get_user_activities($user_id = '') {

  $user_id = !empty($user_id) ? $user_id : DrupalCultureFeed::getLoggedInUserId();

  $activities = &drupal_static(__FUNCTION__, array());
  if (isset($activities[$user_id])) {
    return $activities;
  }

  if ($user_id) {
    $activities[$user_id] = culturefeed_calendar_get_culturefeed_user_activities($user_id);
  }
  else {
    $activities[$user_id] = culturefeed_calendar_get_anonymous_user_activities();
  }

  return $activities[$user_id];
}

/**
 * Get all the calendar activities for a culturefeed user.
 */
function culturefeed_calendar_get_culturefeed_user_activities($user_id) {

  $activities = new stdClass();
  $activities->objects = array();
  $activities->total = 0;

  // Only search for activities with type_like or type_ik_ga.
  $activity_options = array(
    CultureFeed_Activity::TYPE_LIKE,
    CultureFeed_Activity::TYPE_IK_GA,
  );

  $query = new CultureFeed_SearchActivitiesQuery();
  $query->max = 500;
  $query->type = $activity_options;
  $query->contentType = 'event';
  $query->userId = $user_id;

  try {
    $activities = DrupalCultureFeed::searchActivities($query);
  }
  catch (Exception $e) {
    watchdog_exception('culturefeed_calendar', $e);
  }

  return $activities;

}

/**
 * Get the calendar activities for an anonymous user.
 */
function culturefeed_calendar_get_anonymous_user_activities() {

  $activities = new stdClass();
  $activities->objects = array();
  $activities->total = 0;

  // No cookie = no activities
  if (isset($_COOKIE['Drupal_visitor_calendar'])) {

    $calendar = json_decode($_COOKIE['Drupal_visitor_calendar']);
    // Check if cookie is valid.
    if (is_array($calendar)) {
      $activities->objects = $calendar;
      $activities->total = count($activities->objects);
    }

  }

  return $activities;

}

/**
 * Render the buttons to go to the calendar page or add item form.
 */
function culturefeed_calendar_render_calendar_buttons($item) {

  $authenticated = DrupalCultureFeed::isCultureFeedUser();
  $id = $item->getId();
  $locations = array('content', 'footer');
  $actions = array('view', 'add');
  $buttons = array();
  $button = array();

  $button['item_id'] = $id;

  $ids_to_check = array();
  $activities = NULL;
  if ($authenticated) {
    $activities = culturefeed_calendar_get_user_activities();
    if (isset($activities->objects)) {
      foreach($activities->objects as $key => $activity) {
        $ids_to_check[] = $activity->nodeId;
      }
    }
  }

  foreach ($locations as $location) {

    $button['location'] = $location;

    // Show the correct button for authenticated users.
    if ($authenticated) {

      if (in_array($id, $ids_to_check)) {
        $action = 'view';
      }
      else {
        $action = 'add';
      }

      $button['action'] = $action;
      $buttons[$location][$action] = theme('culturefeed_calendar_button', array('button' => $button, 'authenticated' => $authenticated));
    }
    // Show both buttons for anonymous users. JS will show the correct one.
    else {
      foreach ($actions as $action) {
        $button['action'] = $action;
        $buttons[$location][$action] = theme('culturefeed_calendar_button', array('button' => $button, 'authenticated' => $authenticated));
      }
    }
  }
  return $buttons;
}

/**
 * Helper function to add an activity to the calendar.
 */
function culturefeed_calendar_add_activity($node_id, $node_title, $date) {

  $authenticated = DrupalCultureFeed::isCultureFeedUser();

  if ($authenticated) {
    $activity = new CultureFeed_Activity();
    if (!empty($date)) {
      $selection = new stdClass();
      $selection->calendar_date = strtotime($date);
      $activity->value = json_encode($selection);
      $activity->type = CultureFeed_Activity::TYPE_IK_GA;
    }
    else {
      $activity->type = CultureFeed_Activity::TYPE_LIKE;
    }

    $activity->contentType = 'event';
    $activity->nodeId = $node_id;
    $activity->nodeTitle = $node_title;
    $activity->userId = DrupalCultureFeed::getLoggedInUserId();

    DrupalCultureFeed::createActivity($activity);
  }
  else {
    $activity = new stdClass();

    if (!empty($date)) {
      $selection = new stdClass();
      $selection->calendar_date = strtotime($date);
      $activity->value = json_encode($selection);
      $activity->type = CultureFeed_Activity::TYPE_IK_GA;
    }
    else {
      $activity->type = CultureFeed_Activity::TYPE_LIKE;
    }
    $activity->nodeId = $node_id;

    $calendar = array();

    if (isset($_COOKIE['Drupal_visitor_calendar'])) {
      $calendar = json_decode($_COOKIE['Drupal_visitor_calendar']);
      // Invalid cookie value, reset again.
      if (!is_array($calendar)) {
        $calendar = array();
      }
    }

    $calendar[] = $activity;
    end($calendar);
    $last_key = key($calendar);
    $calendar[$last_key]->id = $last_key;
    $values = array(
      'calendar' => json_encode($calendar),
    );

    user_cookie_save($values);

  }

}

/**
 * Checks wether an event has multiple dates.
 */
function culturefeed_calendar_event_has_multiple_dates($dates_array) {

  switch ($dates_array['type']) {

    case 'period':
      return ($dates_array['period_start'] == $dates_array['period_end']) ? FALSE : TRUE;

    case 'permanent':
      return TRUE;

    case 'timestamps':
      return (count($dates_array['timestamps']) > 1) ? TRUE : FALSE;

  }

}

/**
 * Updates a calendar event in the cookie for anonymous users.
 *
 * @param CultureFeed_Activity $activity
 * @param string $date String version of the date to save.
 */
function culturefeed_calendar_update_calendar_event_cookie($activity, $date) {

  if (isset($_COOKIE['Drupal_visitor_calendar'])) {

    $calendar = json_decode($_COOKIE['Drupal_visitor_calendar']);
    if (is_array($calendar) && isset($calendar[$activity->id])) {
      $selection = new stdClass();
      $selection->calendar_date = strtotime($date);
      $calendar[$activity->id]->value = json_encode($selection);
      $calendar[$activity->id]->type = CultureFeed_Activity::TYPE_IK_GA;
    }
    else {
      return FALSE;
    }

    $values = array(
      'calendar' => json_encode($calendar),
    );

    user_cookie_save($values);

    return TRUE;
  }

  return FALSE;

}

/**
 * deletes a calendar event from the cookie for anon users.
 *
 * @param CultureFeed_Activity $activity
 */
function culturefeed_calendar_delete_calendar_event_cookie($activity) {
  if (isset($_COOKIE['Drupal_visitor_calendar'])) {

    $calendar = json_decode($_COOKIE['Drupal_visitor_calendar']);
    if (is_array($calendar) && isset($calendar[$activity->id])) {
      unset($calendar[$activity->id]);
    }
    else {
      return FALSE;
    }

    // Reset the keys to become numeric again.
    $calendar = array_values($calendar);
    // Also reset the ids.
    foreach ($calendar as $key => $calendar_item) {
      $calendar[$key]->id = $key;
    }


    $values = array(
      'calendar' => json_encode($calendar),
    );

    user_cookie_save($values);

    return TRUE;
  }

  return FALSE;
}

/**
 * Get the calendar date that is selected for an activity.
 */
function culturefeed_calendar_get_selected_date($activity) {

  if (isset($activity->value)) {
    $calendar_info = json_decode($activity->value);
    if ($calendar_info && !empty($calendar_info->calendar_date)) {
      return $calendar_info->calendar_date;
    }
  }

}

/**
 * Helper function to sort activities by date.
 */
function culturefeed_calendar_sort_by_date( $a, $b ) {

    return json_decode($a->value)->calendar_date - json_decode($b->value)->calendar_date;
}
