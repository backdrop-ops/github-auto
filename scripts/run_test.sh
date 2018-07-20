#!/bin/sh
# This script start tests on test server.

#just testing
SITEPATH="$HOME/www"

echo "Full site path: $SITEPATH"
cd $SITEPATH

# Install and run backdrop/coder
composer require backdrop/coder
./vendor/bin/phpcs --standard=./vendor/backdrop/coder/coder_sniffer/Backdrop core

# Run the Backdrop test suites.
php core/scripts/run-tests.sh --url http://localhost --verbose --cache --force --class UserAccountLinksUnitTests
