<?php

class views_handler_field_twitter_web_intents_reply_link extends views_handler_field_twitter_web_intents_link {

  protected $default_text = 'Reply';

  function render($values){
    return parent::render_link('https://twitter.com/intent/tweet?in_reply_to=' . $values->twitter_id);
  }

}
