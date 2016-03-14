<?php
/**
 * @file
 * Administration pages provided by github API module.
 */

 /**
 * Menu callback for admin/config/system/githubapi/settings.
 */
function githubapi_admin_settings() {
  $config = config('rp_api.settings');
  $form['server'] = array(
    '#type' => 'textfield',
    '#title' => t('Server'),
    '#default_value' => $config->get('server'),
    '#description' => t('RobinPanel server IP or hostname.'),
  );

  $form['username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#default_value' => $config->get('username'),
    '#description' => t('RobinPanel username.'),
  );

  $form['password'] = array(
    '#type' => 'textfield',
    '#title' => t('Password'),
    '#default_value' => $config->get('password'),
    '#description' => t('RobinPanel password.'),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Submit handler for the githubapi_admin_settings() form.
 */
function githubapi_admin_settings_submit($form, &$form_state) {

  $config = config('rp_api.settings');
  $config->set('server', $form_state['values']['server']);
  $config->set('username', $form_state['values']['username']);
  $config->set('password', $form_state['values']['password']);
  $config->save();
  backdrop_set_message(t('The configuration options have been saved.'));
}