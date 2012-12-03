<?php

/**
 * @file
 * Views handler to show Favorite link.
 */

/**
 * Field handler for Favorite link.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_twitter_web_intents_favorite_link extends views_handler_field_twitter_web_intents_link {

  protected $default_text = 'Favorite';

  function render($values){
    return parent::render_link('https://twitter.com/intent/favorite?tweet_id=' . $values->twitter_id);
  }

}
