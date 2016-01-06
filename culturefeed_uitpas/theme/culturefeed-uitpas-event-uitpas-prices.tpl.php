<?php
/**
* @file
* Default theme implementation to display the uitpas prices on an event detail.
*
* Available variables:
* - $distribution_keys: the prices per distribution key.
**/
?>
<div class="event-details-uitpas-prices">
  <h3><?php print t('UiTPAS Reduction'); ?></h3>
  <div class="distribution-keys">
    <?php
     foreach ($distribution_keys_default_render as $distribution_key) {
       print $distribution_key;
     }
    ?>
  </div>
</div>
