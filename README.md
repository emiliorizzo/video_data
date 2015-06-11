# Video Data Module

## Introduction

This module retrieves data from youtube and vimeo APIs.
Some features are similar to video_embed_field field module but can be used to complement it.


###Motivation

- Ad Configurable API KEY for youtube API v3.
- Provide tokens to auto title Videos
- (WiP) Extends html5_media features 

## Description
 This module have 2 modules:
 
### video_data 
 reads and parse video data from Youtube and Vimeo, using URLs from the field types:
 
 - text 
 - video_embed_field  - https://www.drupal.org/project/video_embed_field


### video_data_token
  provides tokens from data reads by video_data module
  
  -id: Video id
  -title: Video title
  -description: Video Description
  -duration: Video duration in seconds 

## Instalation

  - Install as any module and enable it (video_data)
  - To use tokens enable video_data_token module
  - Go to admin/config/media/video_data and set your Youtube KEY API
  
## Example - Node Title form Video Title

 - Download and install video_data module
 - Enable video_data and video_data_token modules
 - Download and install auto_entitylabel - https://www.drupal.org/project/auto_entitylabel
 - Create a Content Type (ex: "videos") 
 - Add a text field or a  video_embed_field (ej "video_link")
 - Goto admin/config/media/video_data and select the field name (in this case "video_link")
   in the select list of your conten type (in this case "videos"), Save Configuration
 - Edit the Conten Type ("videos") Autolabel options, and write (or search in Token Browser)
   this token: [video_data:title]
 - Save Content Type Configuration
 - Create a  "videos" content and write a valid vimeo url in the field "video_link"
 - Save the content, and the content title is automatically set to video title on vimeo 

##Services

 - Vimeo API v2
 - YouTube API v3 

Youtube v3 API requires a API KEY to retrieve data, get it from code.google.com
and save in admin/config/media/video_data (youtube_api_key field)


## Limitations

- Map only one field (video_embed_field  or text) per Content Type
- Retrieves only one value per field , multivalues fields are not supported.

