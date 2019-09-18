Error Log
=========

Once Drupal 7 bootstraps, it stops sending errors to PHP's error log — which
could be the web server error log, syslog, or stderr on the command line.

Error Log module adds the PHP error log as a Drupal watchdog implementation,
so errors will once again appear in the same log or console that they appeared
in before Drupal bootstrapped.

Drush provides its own console logger. Error Log module is therefore not active
in the Drush environment, unless the error_log configuration directive has been
set.

In the future we may add features such as log format configuration, etc.
However, if you need more features, you are encouraged to try Monolog:
https://www.drupal.org/project/monolog

Please file bug reports and feature requests at:
https://www.drupal.org/project/error_log
