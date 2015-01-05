<?php
/**
 * @file
 * Template for the summary of an actor.
 */
?>

<h3><a href="<?php print $url ?>"><?php print $title; ?></a></h3>
<?php if (isset($location['city'])): ?>
<?php print $location['city']; ?>
<?php endif;?>

<?php if (!empty($thumbnail)): ?>
<img src="<?php print $thumbnail; ?>?width=160&height=120&crop=auto" alt="<?php print $title; ?>" />
<?php endif; ?>

<?php print culturefeed_search_detail_l('actor', $cdbid, $title, t('More info'), array('attributes' => array('class' => 'button'))); ?>
