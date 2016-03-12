<?php
/**
 * @file
 * Administration pages provided by github API module.
 */

 /**
 * Menu callback for admin/config/system/githubapi/list.
 */
 
function githubapi_repos(){
  module_load_include('inc', 'githubapi', 'githubapi_class');
  $config = config('githubapi.settings');
  $token = $config->get('token');
  
  $githubapi = new GithubAPI();
    
  $githubapi->setOwnerName('itpatrol');
  $githubapi->setRepoName('test');
  $githubapi->setToken($token); 
  
  $data = $githubapi->getRepo();
  $output = '<pre>' . print_r($data,true). '</pre>';
  return $output;
}
