<?php

/**
 * @class
 * Handler class to handle filtering on activity counts.
 */
class views_handler_filter_culturefeed_search_numeric extends views_handler_filter_numeric {

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

    $startRange = $this->value['value'];
    if (!empty($this->value['max'])) {
      $startRange = $this->value['min'];
      $endRange = $this->value['max'];
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
          $parameter = new \CultuurNet\Search\Parameter\FilterQuery($this->real_field . ':' . $startRange);
          $this->query->add_parameter($parameter);
          return;
      }
    }

    $parameter = new \CultuurNet\Search\Parameter\FilterQuery($this->real_field . ':[' . $startRange . ' TO ' . $endRange . ']');
    $this->query->add_parameter($parameter);
  }

}
