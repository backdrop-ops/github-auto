# Git.lc service integarion scripts

This repository hold scripts for backdrop/backdrop repository to deploy websites by PR.

- scripts/init_deploy.sh : this script calls only once, when PR created or reopened. 
  This script receive next ENV_VARS:
  - $HOME : user home directory /home/qa for now.
  - $DOMAIN : PR website domain name. Depends on borq_qa/.gitlc.yml can be changed there.
  - $GITLC_DEPLOY_DIR : directory where git clone happen.
  - $DATABASE_USER : database username.
  - $DATABASE_NAME : database name.
  - $DATABASE_PASSWORD : password for database.
  - $ACCOUNT_MAIL : depends on borq_qa/.gitlc.yml can be changed there.
  - $SITE_USER : admin
  - $SITE_PASSWORD : random string.
  
See more details in backdrop-ops/backdropcms.org/www/modules/custom/borg_qa/borg_qa.module hook_gitlc_webhook