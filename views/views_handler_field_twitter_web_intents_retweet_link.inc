<?php

class views_handler_field_twitter_web_intents_retweet_link extends views_handler_field_twitter_web_intents_link {

  protected $default_text = 'Retweet';

  function render($values){
    return parent::render_link('https://twitter.com/intent/retweet?tweet_id=' . $values->twitter_id);
  }

}
