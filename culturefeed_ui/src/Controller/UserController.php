<?php

/**
 * @file
 * Contains Drupal\culturefeed_ui\Controller\UserController.
 */

namespace Drupal\culturefeed_ui\Controller;

use Drupal\Core\Controller\ControllerBase;
use Symfony\Component\DependencyInjection\ContainerInterface;
use CultureFeed_User;

/**
 * Class UserController.
 *
 * @package Drupal\culturefeed_ui\Controller
 */
class UserController extends ControllerBase
{
    /**
     * The culturefeed user service.
     *
     * @var CultureFeed_User;
     */
    protected $user;

    /**
     * {@inheritdoc}
     */
    public static function create(ContainerInterface $container) {
        return new static(
            $container->get('culturefeed.current_user')
        );
    }

    /**
     * Constructs a ProfileForm
     *
     * @param CultureFeed_User $user
     */
    public function __construct(
        CultureFeed_User $user
    ) {
        $this->user = $user;
    }

    /**
     * Profile.
     *
     * @return string
     *   Return Hello string.
     */
    public function profile()
    {
//        var_dump($this->user);
//        die();

        $renderArray = [
            '#theme' => 'ui_profile',
            '#user' => $this->user,
        ];

        return $renderArray;
    }

}