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

  public function init(&$view, &$options) {
    parent::init($view, $options);
    if ($this->handler_type == 'empty') {
      $this->options['empty'] = TRUE;
    }
  }

  public function label() {
    if (!isset($this->options['label'])) {
      return $this->ui_name();
    }
    return $this->options['label'];
  }

  public function get_link_options() {

    $cached_attributes = &drupal_static('twitter_web_intents_attrs_area_' . $this->view->dom_id . '_' . $this->handler_type . '_' . $this->options['id'], FALSE);

    if ($cached_attributes === FALSE) {
      $given_options = array();
      $given_options['attributes'] = array();

      $option_keys = array(
        'title' => 'link_title',
        'name' => 'link_name',
        'rel' => 'link_rel',
        'class' => 'link_classes',
        'style' => 'link_style',
        'target' => 'link_target',
      );

      foreach ($option_keys as $attribute => $option_key) {
        if (isset($this->options[$option_key]) && $this->options[$option_key]) {
          $given_options['attributes'][$attribute] = $this->options[$option_key];
        }
      }

      $cached_attributes = $given_options;

      return $given_options;

    }
    else {

      return $cached_attributes;

    }

  }

  public function option_definition() {
    $options = parent::option_definition();
    $this->definition['field'] = !empty($this->definition['field']) ? $this->definition['field'] : '';
    $label = !empty($this->definition['label']) ? $this->definition['label'] : $this->definition['field'];
    $options['label'] = array('default' => $label, 'translatable' => TRUE);
    $options['text'] = array('default' => 'Follow', 'translatable' => TRUE);
    $options['empty'] = array('default' => FALSE, 'bool' => TRUE);
    $options['follow_mode'] = array('default' => 0, 'translatable' => FALSE);
    $options['follow_username'] = array('default' => 'twitter', 'translatable' => FALSE);
    $options['follow_userid'] = array('default' => '783214', 'translatable' => FALSE);
    $options['link_title'] = array('default' => '', 'translatable' => TRUE);
    $options['link_name'] = array('default' => '', 'translatable' => FALSE);
    $options['link_rel'] = array('default' => '', 'translatable' => FALSE);
    $options['link_classes'] = array('default' => '', 'translatable' => FALSE);
    $options['link_style'] = array('default' => '', 'translatable' => FALSE);
    $options['link_target'] = array('default' => '', 'translatable' => FALSE);
    return $options;
  }

  public function admin_summary() {
    return $this->label();
  }

  public function options_form(&$form, &$form_state){
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
    $form['link_options'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Link options'),
    );
    $form['link_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#description' => t('The description displayed when hovering over the link.'),
      '#default_value' => $this->options['link_title'] ? $this->options['link_title'] : '',
      '#fieldset' => 'link_options',
    );
    $form['link_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Name'),
      '#fieldset' => 'link_options',
      '#default_value' => $this->options['link_name'] ? $this->options['link_name'] : '',
    );
    $form['link_rel'] = array(
      '#type' => 'textfield',
      '#title' => t('Relationship'),
      '#description' => t("Specifies the relationship between the current page and the link. Enter 'nofollow' here to nofollow this link."),
      '#fieldset' => 'link_options',
      '#default_value' => $this->options['link_rel'] ? $this->options['link_rel'] : '',
    );
    $form['link_classes'] = array(
      '#type' => 'textfield',
      '#title' => t('Classes'),
      '#description' => t('Enter additional classes to be added to the link.'),
      '#fieldset' => 'link_options',
      '#default_value' => $this->options['link_classes'] ? $this->options['link_classes'] : '',
    );
    $form['link_style'] = array(
      '#type' => 'textfield',
      '#title' => t('Style'),
      '#description' => t('Enter additional styles to be applied to the link.'),
      '#fieldset' => 'link_options',
      '#default_value' => $this->options['link_style'] ? $this->options['link_style'] : '',
    );
    $form['link_target'] = array(
      '#type' => 'select',
      '#title' => t('Target'),
      '#required' => FALSE,
      '#options' => array(
        '' => 'None (i.e. same window)',
        '_blank' => 'New window (_blank)',
        '_top' => 'Top window (_top)',
        '_self' => 'Same window (_self)',
        '_parent' => 'Parent window (_parent)',
      ),
      '#description' => t('Specifies where to open the link. Using this attribute breaks XHTML validation.'),
      '#fieldset' => 'link_options',
      '#default_value' => $this->options['link_target'] ? $this->options['link_target'] : '',
    );
  }

  public function query() {
    return NULL;
  }

  public function render($empty = FALSE) {
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
      return l($this->options['text'], 'https://twitter.com/intent/user' . $query, $this->get_link_options());
    }
    else {
      return l(t('Follow'), 'https://twitter.com/intent/user' . $query, $this->get_link_options());
    }
  }

  public function use_group_by() {
    return FALSE;
  }

}
