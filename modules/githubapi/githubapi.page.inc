<?php
/**
 * @file
 * Administration pages provided by github API module.
 */

 /**
 * Menu callback for admin/config/system/githubapi/list.
 */

function githubapi_repos(){
  $output = backdrop_get_form('githubapi_hook');
  return $output;
}

function githubapi_hook(){
  $form['owner_repo_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Please provide owner/repo'),
    '#description' => t('Please put in format owner/repo.'),
  );
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Hook repo'),
  );

  return $form;

}

/**
 * Submit handler for the githubapi_hook() form.
 */
function githubapi_hook_submit($form, &$form_state) {

  $owner_repo = explode("/", $form_state['values']['owner_repo_path']);

  module_load_include('inc', 'githubapi', 'githubapi_class');
  $config = config('githubapi.settings');
  $token = $config->get('token');

  $githubapi = new GithubAPI();

  $githubapi->setOwnerName($owner_repo[0]);
  $githubapi->setRepoName($owner_repo[1]);
  $githubapi->setToken($token);

  $data = $githubapi->getRepo();
  backdrop_set_message('<pre>' . print_r($data,true). '</pre>');
}
