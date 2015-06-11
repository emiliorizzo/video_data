<?php

/**
 * @file
 * Admin page callbacks for the video_data module.
 */

/**
 * Form builder; Configure video_data module
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function video_data_admin_form($form, &$form_state){

 $form['#tree'] = TRUE;
 
  /* Main Fieldset */
 $form['video_data'] = array(
    '#type' => 'fieldset',
    '#title' => t('Video Data Settings'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
 
  /* Youtube Fieldset */
  $form['video_data']['youtube'] = array(
    '#type' => 'fieldset',
    '#title' => t('Youtube Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  
  $form['video_data']['youtube']['api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Youtube API KEY'),
    '#default_value' => variable_get('video_data_youtube_api_key', NULL),
    '#description' => t("Enter Your Youtube API KEY here"),
  );
  
  /* Token Configuration */
  if( module_exists('video_data_token') ){
    
   $map = unserialize(variable_get('video_data_map',NULL));
   /* Map Configuration Fieldset */
   $form['video_data']['map'] = array(
     '#type' => 'fieldset',
     '#title' => t('Token Settings'),
     '#collapsible' => TRUE,
     '#collapsed' => FALSE,
   );
   
   $fd =  _video_data_admin_fields_array();
   if( $fd ){
    foreach( $fd as $ct => $fa ){
     $form['video_data']['map'][$ct] = array('#type' => 'select',
                                             '#title' => $ct,
                                             '#options' => $fa,
                                             '#default_value' => $map[$ct],
                                             '#description' => t('Select Video Field on @ct Content Type',array('@ct'=>$ct)),
                                             '#empty_value'=>0,
                                             '#empty_option'=>'--'.t('None').'--',
                                             );
                                         
    }
   }
 }
  
 $form = system_settings_form($form);
 array_unshift($form['#submit'], 'video_data_admin_form_submit');
 return $form; 
}

function video_data_admin_form_submit($form, &$form_state){
 $form_state['values']['video_data_map'] = serialize($form_state['values']['video_data']['map']); 
 $form_state['values']['video_data_youtube_api_key'] = $form_state['values']['video_data']['youtube']['api_key'];
 unset($form_state['values']['video_data']);
}


function _video_data_admin_fields_array(){
 /* Field types that may contain video URL  */
 $types = array_keys(_video_data_fields_types());
 
 $fields =  field_info_field_map();
 $ret = array();

  foreach( $fields as $f => $fd ){
   
   if( array_search($fd['type'], $types) !== FALSE ){
     if( isset($fd['bundles']['node']) &&  is_array($fd['bundles']['node']) ){
      foreach( $fd['bundles']['node'] as $ct ){
        $ret[$ct][$f] = $f;
      }
    }
   }
 }
 if( count($ret) > 0 ) return $ret; 
 return false;
 
}
