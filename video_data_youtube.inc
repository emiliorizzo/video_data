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

      $pos2 = _video_embed_get_min($pos2, $pos_hash);
    }
    else {
      $pos = strripos($url, '/');
      if ($pos !== FALSE) {
        $pos++;
        $pos2 = stripos($url, '?', $pos);
        $pos_hash = stripos($url, '#', $pos);

        $pos2 = _video_embed_get_min($pos2, $pos_hash);
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
