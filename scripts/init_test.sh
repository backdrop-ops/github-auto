#!/bin/sh
# This script create a website ON test server.

#set site path
SITEPATH="$HOME/www"

# Go to domain dir.
cd $SITEPATH

#install backdrop

php $SITEPATH/core/scripts/install.sh  --db-url=mysql://test:localhost/test