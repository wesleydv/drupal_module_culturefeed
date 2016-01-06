<?php
/**
* @file
* Default theme implementation to display the uitpas price by distribution key
* on an event detail.
*
* Available variables:
* - $distribution_keys: the prices per distribution key.
**/
?>
<div class="event-details-uitpas-price">
  <?php print $name; ?>
  <?php print $reduced_price; ?>
  <?php print $price_classes; ?>
</div>
