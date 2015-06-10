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
 
/**
 * Get video data for a Vimeo video URL.
 *
 * @param string $url
 *   A Vimeo video URL to get data for.
 *
 * @return array|false
 *   An array of video data, or FALSE if unable to fetch data.
 */
function video_data_vimeo_handle_data($url) {
  // Get ID of video from URL.
  $id = _video_embed_field_get_vimeo_id($url);
  if ($id) {
    $response = drupal_http_request('http://vimeo.com/api/v2/video/' . $id . '.php');
    if (!isset($response->error)) {
      $response = unserialize($response->data);
      return (array) current($response);
    }
  }
  return FALSE;
}
 
function  _video_data_vimeo_parse_data($data){
 return array( 'title' => $data['title'],
               'description' => $data['description'],
               'service' => 'vimeo',
               'vimeo' => $data,
             ); 
}