# Video Data Module

## Introduction

This module retrieves data from Youtube and Vimeo APIs.
Some features are similar to video_embed_field field module but can be used to complement it.


###Motivation

- Add Configurable Youtube API KEY v3.
- Provide tokens to auto title Videos
- (WiP) Extends html5_media features 

## Description
 The main module is:
 
### video_data 
 reads and parse video data from Youtube and Vimeo, using URLs from the field types:
 
 - text 
 - video_embed_field  - https://www.drupal.org/project/video_embed_field

This module have 1 submodule:

### video_data_token
  provides tokens from data reads by video_data module
  
  - id: Video id
  - title: Video title
  - description: Video Description
  - duration: Video duration in seconds 

## Instalation

  - Install as any module and enable it (video_data)
  - To use tokens enable video_data_token module
  - Go to admin/config/media/video_data and set your Youtube KEY API
  
## Example - Node Title from Video Title

 - Download and install video_data module
 - Enable video_data and video_data_token modules
 - Download and install auto_entitylabel - https://www.drupal.org/project/auto_entitylabel
 - Create a Content Type (ex: "videos") 
 - Add a text field or a  video_embed_field (ej "video_link")

 - Goto admin/config/media/video_data, 
 -- ... in the select list of your content type (in this case "videos")
 -- -> select the field name (in this case "video_link")
 --  -> Save Configuration

 - Edit the Content Type ("videos") -> Autolabel options
 -- -> Write (or search in Token Browser)
 -- -> this token: [video_data:title]
 - Save Content Type configuration

 - Create a  "videos" content and write a valid vimeo url in the field "video_link"
 - Save the content, and the content title is automatically set to video title on vimeo 

##Services

 - Vimeo API v2
 - YouTube API v3 

Youtube v3 API requires a API KEY to retrieve data.
 https://developers.google.com/youtube/v3/getting-started

** Save your API KEY in admin/config/media/video_data (youtube_api_key field) **


## Limitations

- Maps only one field (video_embed_field  or text) per content type
- Retrieves only one value per field , multivalues fields are not supported.

