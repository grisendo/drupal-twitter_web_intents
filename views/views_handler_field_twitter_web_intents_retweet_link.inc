<?php

/**
 * @file
 * Views handler to show Retweet link field.
 */

/**
 * Field handler for Retweet link.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_twitter_web_intents_retweet_link extends views_handler_field_twitter_web_intents_link {

  protected $default_text = 'Retweet';

  public function option_definition() {
    $options = parent::option_definition();
    $options['retweet_related'] = array('default' => '', 'translatable' => FALSE);
    return $options;
  }

  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['retweet_options'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Retweet options'),
    );
    $form['retweet_related'] = array(
      '#type' => 'textfield',
      '#title' => t('Retweet related'),
      '#default_value' => $this->options['retweet_related'] ? $this->options['retweet_related'] : '',
      '#fieldset' => 'retweet_options',
    );
  }

  public function render($values){
    $link = 'https://twitter.com/intent/retweet?tweet_id=' . $values->twitter_id;
    $link .= $this->build_parameters(
      array(
        'retweet_related' => array(
          'parameter' => 'related',
          'escape_mode' => 1,
        ),
      )
    );
    return parent::render_link($link);
  }

}
