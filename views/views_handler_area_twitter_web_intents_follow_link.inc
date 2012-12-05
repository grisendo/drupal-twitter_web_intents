<?php

/**
 * @file
 * Views handler to show Follow link area.
 */

/**
 * Area handler for Follow link.
 *
 * @ingroup views_area_handlers
 */
class views_handler_area_twitter_web_intents_follow_link extends views_handler {

  function init(&$view, &$options) {
    parent::init($view, $options);
    if ($this->handler_type == 'empty') {
      $this->options['empty'] = TRUE;
    }
  }

  function label() {
    if (!isset($this->options['label'])) {
      return $this->ui_name();
    }
    return $this->options['label'];
  }

  function option_definition() {
    $options = parent::option_definition();
    $this->definition['field'] = !empty($this->definition['field']) ? $this->definition['field'] : '';
    $label = !empty($this->definition['label']) ? $this->definition['label'] : $this->definition['field'];
    $options['label'] = array('default' => $label, 'translatable' => TRUE);
    $options['text'] = array('default' => 'Follow', 'translatable' => TRUE);
    $options['empty'] = array('default' => FALSE, 'bool' => TRUE);
    $options['follow_mode'] = array('default' => 0, 'translatable' => FALSE);
    $options['follow_username'] = array('default' => 'twitter', 'translatable' => FALSE);
    $options['follow_userid'] = array('default' => '783214', 'translatable' => FALSE);
    return $options;
  }

  function admin_summary() {
    return $this->label();
  }

  function options_form(&$form, &$form_state){
    parent::options_form($form, $form_state);
    $form['label'] = array(
      '#type' => 'textfield',
      '#title' => t('Label'),
      '#default_value' => isset($this->options['label']) ? $this->options['label'] : '',
      '#description' => t('The label for this area that will be displayed only administratively.'),
    );
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text'),
      '#default_value' => isset($this->options['text']) ? $this->options['text'] : 'Follow',
    );
    if ($form_state['type'] != 'empty') {
      $form['empty'] = array(
        '#type' => 'checkbox',
        '#title' => t('Display even if view has no result'),
        '#default_value' => isset($this->options['empty']) ? $this->options['empty'] : 0,
      );
    }
    $form['follow_options'] = array(
      '#title' => t('Follow options'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['follow_mode'] = array(
      '#title' => t('Mode'),
      '#type' => 'radios',
      '#options' => array(
        0 => t('User screen name'),
        1 => t('User ID'),
      ),
      '#required' => TRUE,
      '#default_value' => isset($this->options['follow_mode']) ? $this->options['follow_mode'] : 0,
      '#fieldset' => 'follow_options',
    );
    $form['follow_username'] = array(
      '#title' => t('User screen name'),
      '#type' => 'textfield',
      '#default_value' => isset($this->options['follow_username']) ? $this->options['follow_username'] : 0,
      '#fieldset' => 'follow_options',
    );
    $form['follow_userid'] = array(
      '#title' => t('User ID'),
      '#type' => 'textfield',
      '#default_value' => isset($this->options['follow_userid']) ? $this->options['follow_userid'] : 0,
      '#fieldset' => 'follow_options',
    );
  }

  function query() {
    return NULL;
  }

  function render($empty = FALSE) {
    if ($this->options['follow_mode']) {
      if (isset($this->options['follow_userid']) && $this->options['follow_userid']) {
        $query = '?user_id=' . $this->options['follow_userid'];
      }
      else {
        $query = '?user_id=783214';
      }
    }
    else {
      if (isset($this->options['follow_username']) && $this->options['follow_username']) {
        $query = '?screen_name=' . $this->options['follow_username'];
      }
      else {
        $query = '?screen_name=twitter';
      }
    }
    if (isset($this->options['text']) && $this->options['text']) {
      return l($this->options['text'], 'https://twitter.com/intent/user' . $query);
    }
    else {
      return l(t('Follow'), 'https://twitter.com/intent/user' . $query);
    }
  }

  function use_group_by() {
    return FALSE;
  }

}
