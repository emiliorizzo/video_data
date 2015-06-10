<?php
/**
 * @file
 * Video Data Vimeo
 */

 /* Return video ID from vimeo URL */
function _video_data_vimeo_id($url){
  $pos = strripos($url, '/');
  if ($pos != FALSE) {
    $pos += 1;
    return (int) substr($url, $pos);
  }
  return FALSE;
}
