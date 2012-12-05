<?php

/**
 * @file
 * Views handler to show Reply link field.
 */

/**
 * Field handler for Reply link.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_twitter_web_intents_reply_link extends views_handler_field_twitter_web_intents_link {

  protected $default_text = 'Reply';

  public function option_definition() {
    $options = parent::option_definition();
    $options['reply_url'] = array('default' => '', 'translatable' => FALSE);
    $options['reply_via'] = array('default' => '', 'translatable' => FALSE);
    $options['reply_text'] = array('default' => '', 'translatable' => FALSE);
    $options['reply_hashtags'] = array('default' => '', 'translatable' => FALSE);
    $options['reply_related'] = array('default' => '', 'translatable' => FALSE);
    return $options;
  }

  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['reply_options'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Reply options'),
    );
    $form['reply_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Reply URL'),
      '#default_value' => $this->options['reply_url'] ? $this->options['reply_url'] : '',
      '#fieldset' => 'reply_options',
    );
    $form['reply_via'] = array(
      '#type' => 'textfield',
      '#title' => t('Reply via'),
      '#default_value' => $this->options['reply_via'] ? $this->options['reply_via'] : '',
      '#fieldset' => 'reply_options',
    );
    $form['reply_text'] = array(
      '#type' => 'textfield',
      '#title' => t('Reply text'),
      '#default_value' => $this->options['reply_text'] ? $this->options['reply_text'] : '',
      '#fieldset' => 'reply_options',
    );
    $form['reply_hashtags'] = array(
      '#type' => 'textfield',
      '#title' => t('Reply hashtags'),
      '#default_value' => $this->options['reply_hashtags'] ? $this->options['reply_hashtags'] : '',
      '#fieldset' => 'reply_options',
    );
    $form['reply_related'] = array(
      '#type' => 'textfield',
      '#title' => t('Reply related'),
      '#default_value' => $this->options['reply_related'] ? $this->options['reply_related'] : '',
      '#fieldset' => 'reply_options',
    );
  }

  public function render($values) {
    $link = 'https://twitter.com/intent/tweet?in_reply_to=' . $values->twitter_id;
    $link .= $this->build_parameters(
      array(
        'reply_url' => array(
          'parameter' => 'url',
          'escape_mode' => 2,
        ),
        'reply_via' => array(
          'parameter' => 'via',
          'escape_mode' => 0,
        ),
        'reply_text' => array(
          'parameter' => 'text',
          'escape_mode' => 2,
        ),
        'reply_hashtags' => array(
          'parameter' => 'hashtags',
          'escape_mode' => 0,
        ),
        'reply_related' => array(
          'parameter' => 'related',
          'escape_mode' => 1,
        ),
      )
    );
    return parent::render_link($link);
  }

}
