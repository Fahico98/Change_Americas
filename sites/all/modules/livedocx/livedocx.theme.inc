<?php

function theme_livedocx_manage_templates_form($variables) {
  $elements = $variables['elements'];
  $table = array();

  // Add table headers and attributes.
  foreach (array('header', 'attributes') as $key) {
    if (isset($elements["#$key"])) {
      $table[$key] = $elements["#$key"];
    }
  }

  // Add form rows, in the order determined at pre-render time.
  foreach (element_children($elements) as $name) {
    $element = $elements[$name];

    $row = array('data' => array());
    if (isset($element['#attributes'])) {
      $row += $element['#attributes'];
    }

    // Render children as table cells.
    foreach (element_children($element) as $cell_key) {
      $child = &$element[$cell_key];
      // Do not render a cell for children of #type 'value'.
      if (!(isset($child['#type']) && $child['#type'] == 'value')) {
      $cell = array('data' => drupal_render($child));
        if (isset($child['#cell_attributes'])) {
          $cell += $child['#cell_attributes'];
        }
        $row['data'][] = $cell;
      }
    }
    $table['rows'][] = $row;
  }

  return theme('table', $table);
}

function theme_livedocx_template_edit_form($variables){
  $elements = $variables['elements'];
  $table = array();

  // Add table headers and attributes.
  foreach (array('header', 'attributes') as $key) {
    if (isset($elements["#$key"])) {
      $table[$key] = $elements["#$key"];
    }
  }

  // Add form rows, in the order determined at pre-render time.
  foreach (element_children($elements) as $name) {
    $element = $elements[$name];

    $row = array('data' => array());
    if (isset($element['#attributes'])) {
      $row += $element['#attributes'];
    }

    // Render children as table cells.
    foreach (element_children($element) as $cell_key) {
      $child = &$element[$cell_key];
      // Do not render a cell for children of #type 'value'.
      if (!(isset($child['#type']) && $child['#type'] == 'value')) {
        $cell = array('data' => drupal_render($child));
        if (isset($child['#cell_attributes'])) {
          $cell += $child['#cell_attributes'];
        }
        $row['data'][] = $cell;
      }
    }
    $table['rows'][] = $row;
  }

  return theme('table', $table);
}
