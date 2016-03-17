<?php

/**
 * @file
 * Administer settings for webhook
 */
/**
 * Adding a module settings to work with Github.
 */
function webhook_admin_settings($form, &$form_state) {
  $config = config('webhook.settings');
  $form['api_key'] = array(
    '#title' => t('Webhook token'),
    '#default_value' => $config->get('api_key'),
    '#description' => t('You can obtain API Key on http://git.lc/api/settings page'),
  );
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save API'),
  );  
}

/**
 * Submit handler for the webhook_admin_settings() form.
 */
function webhook_admin_settings_submit($form, &$form_state) {
  $config = config('webhook.settings');
  $config->set('api_key', $form_state['values']['api_key']);
  $config->save();
  backdrop_set_message(t('The configuration options have been saved.'));
}
