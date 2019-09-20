<?php

function livedocx_admin_template_form($form, &$form_state){
  $form['template_name'] = array(
    '#type'     => 'textfield',
    '#title'    => 'Name of template',
    '#required' => TRUE,
    '#size' => 38,
    '#prefix' => '<div id="livedocx-template-setting" '
      . 'style="border:1px solid; '
      . 'border-radius:7px; '
      . 'padding-left:1cm; '
      . 'border-color:#777777 #999999; '
      . '">' #end div
      . '<legend style="color:blue;font-weight:bold;">LiveDocx Templates</legend>',
  );

  $form['template_file'] = array(
    '#type'         => 'managed_file',
    '#title'        => t('Choose a file'),
    '#description'  => t('Upload a microsoft docx file with mail merge variables'),
    '#size'         => 22,
    '#required'     => TRUE,
    '#upload_location' => variable_get('livedocx_path', 'private://templates/'),
    '#upload_validators' => array(
    'file_validate_extensions' => array('docx'),
    )
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Template Document'),
    '#suffix' => '</div>',      
  );

  return $form;
}

function livedocx_admin_template_form_submit($form, &$form_state){
  global $user;

  $file = file_load($form_state['values']['template_file']);
  $file->status = FILE_STATUS_PERMANENT;
  file_save($file);
  file_usage_add($file, 'user', 'user', $user->uid);
  $machine_name = strtolower($form_state['values']['template_name']);
  $machine_name = preg_replace('/[^\da-z]/i', '_', $machine_name);
  $template = array('fid' => $file->fid, 'name' => $form_state['values']['template_name'], 'machine_name' => $machine_name);
  drupal_write_record('livedocx_template', $template);
  $message = t('Template file %file saved.', array('%file' => $form_state['values']['template_name']));
  drupal_set_message($message);
}

function livedocx_admin_manage_templates_form($form, &$form_state){
  //Todo: I think I need to change the PDO fetch mode so I don't have to do the type casting below
  $templates = db_query('SELECT machine_name, name, tid FROM {livedocx_template}')->fetchAllAssoc('machine_name');
  if(!empty($templates)){
    $defaults = variable_get('livedocx_template_mapping', array());
    $entity_options = livedocx_admin_manage_templates_get_entity_options();
    $table = array(
      '#theme' => 'livedocx_manage_templates_form',
      '#tree' => TRUE,
      '#header' => array(
        t('Template Name'),
        t('Entity'),
        t('Type'),
        t('Operations'),
      ),
      '#parent_options' => array(),
      '#attributes' => array(
        'id' => 'livedocx-manage-templates',
      ),
      '#prefix' => '<div id="livedocx-manage-templates">',
      '#suffix' => '</div>',
    );
    //add rows here
    foreach($templates as $template){
      //Todo:  Can we get rid of the type casting by changing the PDO fetch mode above?
      list($machine_name, $name, $tid) = array_values((array) $template);
      if(isset($form_state['values']['templates'][$machine_name]['entity_type'])){
        $selected = $form_state['values']['templates'][$machine_name]['entity_type'];
      }
      else if(isset($defaults[$machine_name]['entity_type'])){
        $selected = $defaults[$machine_name]['entity_type'];
      }
      else{
        $selected = key($entity_options);
      }
      //Todo: Should change to tid (template id) for cleaner submit function
      $table[$machine_name] = array(
        'name' => array(
          '#tree' => TRUE,
          '#markup' => check_plain($name),
          'hidden' => array(
            '#type' => 'hidden',
            '#value'  => $tid,
          ),
        ),
        'entity_type' => array(
          '#type'           => 'select',
          '#title'          => t('Entity mapping for @template', array('@template' => $name)),
          '#title_display'  => 'invisible',
          '#options'        => $entity_options,
          //Todo: Should change to tid (template id) for cleaner submit function
          '#default_value'  => isset($defaults[$machine_name]['entity_type'])? $defaults[$machine_name]['entity_type'] : 'none',
          '#attributes'     => array(
            'class' => array('livedocx-entity-select-' . str_replace('_', '-', $machine_name), 'livedocx-entity-select'),
          ),
          '#ajax' => array(
            'callback' => 'livedocx_admin_manage_templates_bundle_options_callback',
            'wrapper' => 'livedocx-bundle-' . str_replace('_', '-', $machine_name) . '-wrapper',
          ),
        ),
        'bundle'  => array(
          '#type'           => 'select',
          '#title'          => t('Bundle mapping for @template', array('@template' => $name)),
          '#title_display'  => 'invisible',
          '#options'        => array('none', '----'),
          '#default_value'  => 'none',
          '#attributes'     => array(
            'class' => array('livedocx-entity-select-' . str_replace('_', '-', $machine_name)),
          ),
          '#prefix' => '<div id="' . 'livedocx-bundle-' . str_replace('_', '-', $machine_name) . '-wrapper' . '">',
          '#suffix' => '</div>',
          '#options' => livedocx_admin_manage_templates_get_bundle_options($selected),
          '#default_value' => isset($defaults[$machine_name]['bundle'])? $defaults[$machine_name]['bundle'] : 'none',
        ),
      );
      if(isset($defaults[$machine_name]['entity_type']) && isset($defaults[$machine_name]['bundle'])
        && $defaults[$machine_name]['entity_type'] != 'none' && $defaults[$machine_name]['bundle'] != 'none'
      ){
        $table[$machine_name]['operations'] = array(
          '#theme'   => 'item_list',
          '#items'  => array(
            l('Add/Modify Variables', 'admin/config/services/livedocx/templates/' . $machine_name . '/edit'),
//            l('Clone', 'admin/config/services/livedocx/templates/' . $machine_name . '/clone'),
            l('Delete', 'admin/config/services/livedocx/templates/' . $machine_name . '/delete'),
          ),
          '#attributes' => array(
            'class' => array('inline'),
          ),
        );
      }
      else{
        $table[$machine_name]['operations'] = array(
          '#markup' => '&nbsp;',
          '#prefix' => '<div id="' . 'livedocx-operations-' . str_replace('_', '-', $machine_name) . '-wrapper' . '">',
          '#suffix' => '</div>',
        );
      }
    }

    $form['templates'] = $table;
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save'));
    $form['#attached']['js'][] = drupal_get_path('module', 'livedocx') . '/livedocx.js';
  }
  else{
    $link = l(t('here'), 'admin/config/services/livedocx/add');
    $form['message'] = array(
      '#markup' => t('Could not find any microsoft word documents.  Please add some templates !here', array('!here' => $link)),
    );
  }
  return $form;
}

function livedocx_admin_manage_templates_get_entity_options() {
  $entity_options = array();
  $entity_info = entity_get_info();
  foreach ($entity_info as $machine_name => $definition) {
        $entity_options[$machine_name] = t($definition['label']);
    }
    $entity_options = array_merge(array('none' => t('None')), $entity_options);
    if (module_exists('comment')) {
        unset($entity_options['comment']);
    }
    if (module_exists('wysiwyg')) {
        unset($entity_options['wysiwyg_profile']);
    }
    return $entity_options;
}

function livedocx_admin_manage_templates_bundle_options_callback($form, &$form_state){
  $template = $form_state['triggering_element']['#parents'][1];
  return $form['templates'][$template]['bundle'];
}

function livedocx_admin_manage_templates_get_bundle_options($entity_type = '') {
  $bundle_options = array();
  $entity_info = entity_get_info();
  foreach ($entity_info as $machine_name => $definition) {
      foreach ($definition['bundles'] as $bundle_name => $bundle_def) {
            $bundle_options[$machine_name][$bundle_name] = $bundle_def['label'];
        }
    }

    if (module_exists('comment')) {
        unset($bundle_options['comment']);
    }
    if (module_exists('wysiwyg')) {
        unset($bundle_options['wysiwyg_profile']);
    }

    $bundle_options = array_merge(array('none' => array('None')), $bundle_options);
  if (isset($bundle_options[$entity_type])) {
    return $bundle_options[$entity_type];
  }
  else {
    return array();
  }
}

function livedocx_admin_manage_templates_form_submit($form, &$form_state){
  $templates = $form_state['values']['templates'];
  $bundles = variable_get('livedocx_bundles', array());
  foreach ($form_state['values']['templates'] as $template_name => $values) {
     $bundles[$values['bundle']] = $values['entity_type'] . '_' . $values['bundle'];
  }
  variable_set('livedocx_bundles', $bundles);
  foreach($templates as $machine_name => $template_mapping){
    $template_mapping['tid'] = $template_mapping['name']['hidden'];
    unset($template_mapping['name']);
    $count = db_query('SELECT count(tid) FROM {livedocx_template_mapping} WHERE tid=:tid', array(':tid' => $template_mapping['tid']))->fetchField();
    if($count){
      drupal_write_record('livedocx_template_mapping', $template_mapping, array('tid'));
    }
    else {
      drupal_write_record('livedocx_template_mapping', $template_mapping);
    }
  }
  variable_set('livedocx_template_mapping', $form_state['values']['templates']);
  drupal_flush_all_caches();
  drupal_set_message('Template settings saved.');
}

function livedocx_admin_template_edit_form($form, &$form_state, $template){
  //Todo: Fix me!  Options for mapping.  Title should only be able to be selected once
  $mailmerge_variables = livedocx_template_get_mailmerge_variables($template->tid);
  $form['template_name'] = array(
    '#markup' => '<h1>' . $template->name . '</h1>'
  );
  $form['template_id'] = array(
    '#type'   => 'hidden',
    '#value'  => $template->tid,
  );
  $table = array(
    '#theme' => 'livedocx_template_edit_form',
    '#tree' => TRUE,
    '#header' => array(
      t('Variable Name'),
      t('Mapping'),
      t('Operation'),
    ),
    '#parent_options' => array(),
    '#attributes' => array(
      'id' => 'livedocx-template-' . $template->machine_name,
    ),
  );
  if(!empty($mailmerge_variables)){
    foreach($mailmerge_variables as $var){
      $table[$var->vid] = array(
        'name' => array(
          '#tree' => TRUE,
          '#markup' => check_plain($var->name),
          'hidden' => array(
            '#type' => 'hidden',
            '#value' => $var->name
          ),
        ),
        'field_map' => array(
          '#type'     => 'select',
          '#options'   => array(
            'field' => t('Fields in Entity'),
            'title' => t('Entity Title'),
          ),
          '#default_value' => $var->field_map,
        ),
        'operations'  => array(
          '#tree' => true,
          '#type' => 'actions',
          'save'  => array(
            '#type'   => 'submit',
            '#value' => 'Save',
            '#name' => $var->vid,
            '#executes_submit_callback' => TRUE,
          ),
          'delete'  => array(
            '#type'   => 'submit',
            '#value'  => 'Delete',
            '#name' => $var->vid,
            '#executes_submit_callback' => TRUE,
          ),
        ),
      );
    }
  }
  $table['new'] = array(
    'name' => array(
      '#type'   => 'textfield',
      '#title'  => 'New Variable',
      //TODO: This isn't working :-( ... Grrrr
      '#prefix' => "<div id='container-inline'>",
      '#suffix' => '</div>',
    ),
    'field_map' => array(
      '#type'     => 'select',
      '#options'   => array(
        'field' => t('Fields in Entity'),
        'title' => t('Entity Title'),
      ),
      '#default_value' => 'field',
    ),
    'operations'  => array(
      '#type'   => 'submit',
      '#value'  => 'Add',
    ),
  );
  $form['table'] = $table;
  
  $form['redirect'] = array(
    '#type'   => 'button',
    '#value'  => 'Done',
    '#executes_submit_callback' => TRUE,
    '#submit' => array('livedocx_admin_redirect_templates'),
  );
  return $form;
}

function livedocx_admin_template_edit_form_submit($form, &$form_state){
  $status = false;
  $variables = $form_state['values']['table'];
  $tid = $form_state['values']['template_id'];
  $operation = $form_state['clicked_button']['#value'];
  if($operation === 'Save'){
    $vid = $form_state['clicked_button']['#name'];
    $var = $form_state['values']['table'][$vid];
    $var = array('vid' => $vid, 'tid' => $tid, 'name' => $var['name']['hidden'], 'field_map' => $var['field_map']);
    $status = drupal_write_record('livedocx_mailmerge_variable', $var, array('vid'));
    $message = t('Mailmerge variable @name saved.', array('@name' => $var['name']));
  }
  else if($operation === 'Delete'){
    $vid = $form_state['clicked_button']['#name'];
    $name = $form_state['values']['table'][$vid]['name']['hidden'];
    $status = db_delete('livedocx_mailmerge_variable')->condition('vid', $vid)->execute();
    $message = t('Mailmerge variable @name deleted.', array('@name' => $name));
  }
  else if($operation === 'Add'){
    $var = $form_state['values']['table']['new'];
    $var = array('tid' => $tid, 'name' => $var['name'], 'field_map' => $var['field_map']);
    $status = drupal_write_record('livedocx_mailmerge_variable', $var);
    $message = t('Mailmerge variable @name added.', array('@name' => $var['name']));
  }
  if($status){
    drupal_set_message($message);
  }
  else{
    drupal_set_message('There was an error with your request', 'error');
  }
}

function livedocx_admin_settings_form($form, &$form_state){
  $form['livedocx_username'] = array(
    '#title'            => t('LiveDocx Username'),
    '#type'             => 'textfield',
    '#required'         => TRUE,
    '#description'      => t('Please enter your LiveDocx.com username'),
    '#default_value'    => variable_get('livedocx_username', ''),
    '#prefix'           => '<div id="livedocx-com-setting" '
                            . 'style="border:1px solid; '
                            . 'border-radius:7px; '
                            . 'padding-left:1cm; '
                            . 'border-color:#777777 #999999; '
                            . '">' #end div
                            . '<legend style="color:blue;font-weight:bold;">LiveDocx.com Settings</legend>',      
  );
  $form['livedocx_password'] = array(
    '#title'            => t('LiveDocx Password'),
    '#type'             => 'password',
    '#required'         => TRUE,
    '#description'      => t('Please enter your LiveDocx.com password'),
    '#default_value'    => variable_get('livedocx_password', ''),
    '#suffix'           => '</div></br>',      
  );

  
  $form['livedocx_path'] = array(
    '#title'            => t('Server storage path of docx templates'),
    '#type'             => t('textfield'),
    '#default_value'    => variable_get('livedocx_path', 'private://templates/'),
    '#required'         => TRUE,
    '#size'             => 40,
    '#maxlength'        => 255,
    '#description'      => t('Path where the docx template files will be stored on the server.  '
                            . 'A local file system path where files will be stored. This directory must exist and be writable by Drupal. This directory must be relative to the Drupal installation directory and be accessible over the web.'),
    '#prefix'           => '<div id="livedocx-path-setting" '
                            . 'style="border:1px solid; '
                            . 'border-radius:7px; '
                            . 'padding-left:1cm; '
                            . 'border-color:#777777 #999999; '
                            . '">' #end div
                            . '<legend style="color:blue;font-weight:bold;">LiveDocx Module Settings</legend>',
    '#suffix'           => '</div>', 
  );    
  
  return system_settings_form($form);
}

//Todo: Implement clone callback and fix menu title
function livedocx_admin_template_clone() {}

function livedocx_admin_template_delete($form, $form_state) {
        // Clean up database
        db_delete('livedocx_template_mapping')->condition('tid',$form->tid)->execute();
        db_delete('livedocx_mailmerge_variable')->condition('tid',$form->tid)->execute();
        db_delete('livedocx_template')->condition('tid', $form->tid)->execute();
        // Remove stored template file & managed_file database entries
        file_delete(file_load($form->fid), TRUE);
        // Return page back to livedocx templates list
        $message = t('LiveDocx template @name deleted.', array('@name' => $form->name));
        drupal_set_message($message);
        livedocx_admin_redirect_templates();
}

function livedocx_admin_redirect_templates() {
    drupal_goto('admin/config/services/livedocx/templates');
}
