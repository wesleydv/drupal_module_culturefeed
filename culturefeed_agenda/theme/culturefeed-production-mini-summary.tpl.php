<?php
/**
 * @file
 * Template for the mini summary of a production.
 */
?>

<h4><a href="<?php print $url ?>"><?php print $title; ?></a></h4>
<?php if (!empty($themes)): ?>
<p><?php print $themes[0] ?></p>
<?php endif; ?>

<p><?php print $agefrom; ?>

<p>
<?php if (isset($location['city'])): ?>
<?php print $location['city']; ?>
<?php endif;?>
<?php if (!empty($when)): ?>
    <dt><?php print t('When'); ?></dt>
      <?php if (is_array($when)): ?>
        <?php foreach ($when as $date): ?>
          <dd><?php print $date; ?></dd>
        <?php endforeach; ?>
      <?php else: ?>
        <dd><?php print $when; ?></dd>
      <?php endif; ?>
    <?php endif; ?>
</p>

<hr />
