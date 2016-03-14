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
  $form['token'] = array(
    '#type' => 'textfield',
    '#title' => t('Webhook token'),
    '#default_value' => $config->get('token'),
    '#description' => t('You can obtain it on repo setting page on http://git.lc website')
  );
}

/**
 * Submit handler for the webhook_admin_settings() form.
 */
function webhook_admin_settings_submit($form, &$form_state) {
  $config = config('webhook.settings');
  $config->set('token', $form_state['values']['token']);
  $config->save();
  backdrop_set_message(t('The configuration options have been saved.'));
}
