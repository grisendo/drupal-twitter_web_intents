<?php

/**
 * @file
 * Views handler to show a link, to be inherited from others.
 */

/**
 * Main field handler for links.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_twitter_web_intents_link extends views_handler_field {

  protected $default_text = 'Link';
  protected $required_twitter_field = 'twitter_id';

  function construct() {
    parent::construct();
    $this->additional_fields[$this->required_twitter_field] = $this->required_twitter_field;
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['text'] = array('default' => '', 'translatable' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'] ? $this->options['text'] : $this->default_text,
    );
  }

  function render_link($link) {
    if (!isset($this->options['text']) || ! ($this->options['text'])) {
      return l(t($this->default_text), $link);
    }
    else {
      return l(t($this->options['text']), $link);
    }
  }

}
