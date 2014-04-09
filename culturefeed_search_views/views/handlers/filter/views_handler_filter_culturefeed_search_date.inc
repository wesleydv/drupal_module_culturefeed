<?php

/**
 * @class
 * Handler class to handle filtering on date.
 */
class views_handler_filter_culturefeed_search_date extends views_handler_filter_date {

  /**
   * @see views_handler_filter_numeric::operators().
   */
  function operators() {
    $operators = parent::operators();
    unset($operators['regular_expression']);
    return $operators;
  }

  /**
   * @see views_handler_filter::query()
   */
  function query() {

    $startRange = strtotime($this->value['value']);
    if (!empty($this->value['max'])) {
      $startRange = strtotime($this->value['min']);
      $endRange = strtotime($this->value['max']);
    }
    else {

      switch ($this->operator) {

        case '>=':
          $endRange = '*';
          break;

        case '>':
          $startRange += 1;
          $endRange = '*';
          break;

        case '<':
          $endRange = $startRange;
          $startRange = 0;
          break;

        case '<=':
          $endRange = $startRange + 1;
          $startRange = 0;
          break;

        case '==':
          $parameter = new \CultuurNet\Search\Parameter\FilterQuery($this->real_field . ':' . $startRange);
          $this->query->add_parameter($parameter);
          return;


        case '!=':
      }

    }

    $parameter = new \CultuurNet\Search\Parameter\DateRangeFilterQuery($this->real_field, $startRange, $endRange);

    $this->query->add_parameter($parameter);

  }

}
