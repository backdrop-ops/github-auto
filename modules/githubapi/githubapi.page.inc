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

  if($data = $githubapi->getRepo()){
  
    global $base_url;
    global $base_path;
    
    $settings = array(
      'name' => GITHUB_HOOK_NAME,
      'config' => (object) array(
          'url' => $base_url . $base_path . GITHUB_PAYLOAD_PATH,
          'content_type' => GITHUB_PAYLOAD_CONTENT_TYPE,
        ),
      'events' => array ('push', 'pull_request', 'create', 'delete', 'release', 'issues', 'issue_comment', 'follow', 'fork', 'status' , 'commit_comment', 'pull_request_review_comment' ),
      'active' => true,
    );
    $githubapi->reInitCurl();
    $hook = $githubapi->createHook($settings);
    if($hook){
      backdrop_set_message('<pre>' . print_r($hook,true). '</pre>');
      return $hook;
    }
    return FALSE;
    
    backdrop_set_message('<pre>' . print_r($data,true). '</pre>');
  }
}
