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

  return t('Repos list');
}
