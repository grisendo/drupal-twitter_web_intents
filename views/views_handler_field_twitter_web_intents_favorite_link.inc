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

  function option_definition() {
    $options = parent::option_definition();
    $options['favorite_related'] = array('default' => '', 'translatable' => FALSE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['favorite_options'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Favorite options'),
    );
    $form['favorite_related'] = array(
      '#type' => 'textfield',
      '#title' => t('Favorite related'),
      '#default_value' => $this->options['favorite_related'] ? $this->options['favorite_related'] : '',
      '#fieldset' => 'favorite_options',
    );
  }

  function render($values) {
    $link = 'https://twitter.com/intent/favorite?tweet_id=' . $values->twitter_id;
    $link .= $this->build_parameters(
      array(
        'favorite_related' => array(
          'parameter' => 'related',
          'escape_mode' => 1,
        ),
      )
    );
    return parent::render_link($link);
  }

}
