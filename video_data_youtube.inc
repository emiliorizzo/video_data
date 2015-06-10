<?php
/**
 * @file
 * Video Data Youtube
 */

/**
 * Helper function to get the youtube video's id.
 *
 * @param string $url
 *   The video URL.
 *
 * @return string|bool
 *   The video ID, or FALSE in case the ID can't be retrieved from the URL.
 */
function _video_data_youtube_id($url) {
  // Find the ID of the video they want to play from the url.
  if (stristr($url, 'http://')) {
    $url = substr($url, 7);
  }
  elseif (stristr($url, 'https://')) {
    $url = substr($url, 8);
  }

  if (stristr($url, 'playlist')) {
    // Playlists need the appended ampersand to take the options properly.
    $url = $url . '&';
    $pos = strripos($url, '?list=');
    if ($pos !== FALSE) {
      $pos2 = stripos($url, '&');
      $pos2++;
    }
    else {
      return FALSE;
    }
  }
  // Alternate playlist link.
  elseif (stristr($url, 'view_play_list')) {
    $url = $url . '&';
    // All playlist ID's are prepended with PL.
    if (!stristr($url, '?p=PL')) {
      $url = substr_replace($url, 'PL', strpos($url, '?p=') + 3, 0);
    }
    // Replace the links format with the embed format.
    $url = str_ireplace('play_list?p=', 'videoseries?list=', $url);
    $pos = strripos($url, 'videoseries?list=');
    if ($pos !== FALSE) {
      $pos2 = stripos($url, '&');
      $pos2++;
    }
    else {
      return FALSE;
    }
  }
  else {
    $pos = strripos($url, 'v=');
    if ($pos !== FALSE) {
      $pos += 2;
      $pos2 = stripos($url, '&', $pos);
      $pos_hash = stripos($url, '#', $pos);

      $pos2 = _video_data_get_min($pos2, $pos_hash);
    }
    else {
      $pos = strripos($url, '/');
      if ($pos !== FALSE) {
        $pos++;
        $pos2 = stripos($url, '?', $pos);
        $pos_hash = stripos($url, '#', $pos);

        $pos2 = _video_data_get_min($pos2, $pos_hash);
      }
    }
  }
  if ($pos === FALSE) {
    return FALSE;
  }
  else {
    if ($pos2 > 0) {
      $id = substr($url, $pos, $pos2 - $pos);
    }
    else {
      $id = substr($url, $pos);
    }
  }
  return $id;
}

 
/* Return DATA from youtube URL */
function video_data_youtube_handle_data($url){
 $api_key = variable_get('video_data_youtube_api_key', NULL);

  if( !empty($api_key) ){
   $id = _video_data_youtube_id($url);
    
    if ($id) {
     $options['v'] = 3;
     $options['key'] = $api_key;
     $options['part'] = 'snippet';
     $options['id'] = $id; 
    $response =  drupal_http_request(url('https://www.googleapis.com/youtube/v3/videos', array('query' => $options)));
    if (!isset($response->error)) {
      $data = json_decode($response->data);
      return $data->items;
    }
   }
  }
 return FALSE;
}

function  _video_data_youtube_parse_data($data){
 $data = $data[0];
 return array( 'title' => $data -> snippet -> title,
               'description' => $data -> snippet -> description,
               'service' => 'youtube',
               'youtube' => $data,
             ); 
}

