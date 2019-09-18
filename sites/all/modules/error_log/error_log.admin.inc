<?php

/**
 * @file
 * Contains the configuration form for Error Log.
 */

/**
 * Adds Error Log settings form to form.
 *
 * @param array $form
 *   The form definition.
 * @param array $form_state
 *   The form state.
 */
function error_log_settings_form(array &$form, array &$form_state) {
  $form['error_log'] = array(
    '#type' => 'fieldset',
    '#title' => t('Error Log'),
    '#collapsible' => TRUE,
  );
  foreach (watchdog_severity_levels() as $level => $label) {
    $watchdog_levels["level_$level"] = $label;
  }
  $form['error_log']['error_log_levels'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Message levels'),
    '#description' => t('Check the log levels which should be sent to the PHP error log.'),
    '#default_value' => variable_get('error_log_levels', error_log_default_levels()),
    '#options' => $watchdog_levels,
  );
  $form['error_log']['error_log_ignored_types'] = [
    '#type' => 'textarea',
    '#title' => t('Ignored types'),
    '#description' => t('A list of log event types for which messages should not be sent to the PHP error log (one type per line). Commonly-configured types include <em>access denied</em> for 403 errors and <em>page not found</em> for 404 errors.'),
    '#default_value' => variable_get('error_log_ignored_types', ''),
  ];
}
