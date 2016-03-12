<?php
/**
 * @file
 * Administration pages provided by github API module.
 */
 
 /**
 * Menu callback for admin/config/system/githubapi.
 */
function githubapi_admin_settings() {
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
  
  $config = config('githubapi.settings');
  foreach ($form_state['values'] as $key => $value) {
    $config->set($key, $value);
  }
  $config->save();
  backdrop_set_message(t('The configuration options have been saved.'));
}
