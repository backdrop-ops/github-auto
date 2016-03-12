<?php
/**
 * @file
 * Administration pages provided by github API module.
 */

 /**
 * Menu callback for admin/config/system/githubapi.
 */
function githubapi_admin_settings() {
  $config = config('githubapi.settings');
  $form['client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Client ID'),
    '#default_value' => $config->get('client_id'),
    '#description' => t('Client ID from registered APP on /organizations/****/settings/applications.'),
  );

  $form['client_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Client secret'),
    '#default_value' => $config->get('client_secret'),
    '#description' => t('Client secret from registered APP on /organizations/****/settings/applications.'),
  );
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  $token = $config->get('token');
  if(empty($token)){
    $form['actions']['auth'] = array(
      '#type' => 'submit',
      '#value' => t('Get Token for backdrop-ci'),
      '#submit' => array('githubapi_link_user_submit'),
    );
  }else{
    backdrop_set_message(t('Bot linked to github!'));
  }

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

/**
 * Get token handler for the githubapi_admin_settings() form.
 */
function githubapi_link_user_submit($form, &$form_state){
  global $base_url;
  
  $config = config('githubapi.settings');
  $params = array();
  $params['client_id'] = $config->get('client_id');
  $params['scope'] = GITHUB_SCOPE;

  $params['redirect_uri'] = $base_url . '/githubapi/register';

  $query = http_build_query($params);

  $link = GITHUB_URI . '/login/oauth/authorize?' . $query;

  backdrop_goto($link, array('absolute' => TRUE));

}

/**
 * Menu callback; Process an Github authentication.
 */
function githubapi_get_access_token() {

  if (isset($_GET['code'])) {
    $config = config('githubapi.settings');

    $params = array();
    $params['client_id'] = $config->get('client_id');
    $params['client_secret'] = $config->get('client_secret');
    $params['code'] = filter_xss($_GET['code']);

    $query = http_build_query($params);
    $response = file_get_contents(GITHUB_URI . '/login/oauth/access_token?' . $query);

    parse_str($response, $result);

    if (isset($result['access_token'])) {
      $token = $result['access_token'];
      $config->set('token', $token);
      $config->save();
      backdrop_set_message(t('We connected to GitHub now .'));
      backdrop_goto();
    }
  }
  // If we didn't get a token or code, connection to Github failed.
  backdrop_set_message(t('Failed connecting to GitHub.'), 'error');
  backdrop_goto();
}
