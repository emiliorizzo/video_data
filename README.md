# Video Data Module

## Introduction
 This module have 2 modules:
 
  ### video_data 
      reads video data from Youtube and Vimeo, using URLs from field types:
   
        - text 
        - video_embed_field (see https://www.drupal.org/project/video_embed_field)


  ### video_data_token, 
  
   provides tokesn from data reads by video_data module
   (at momenn the unique token abailable is "title")


## Example usage

 - Download and install video_data module
 - Enable video_data and video_data_token modules
 - Download and install auto_entity_label
 - Create a content type (ex: "videos") 
 - Add a text field or a  - video_embed_field (ej "video_link")
 - Goto admin/config/media/video_data and select the field name (in this case "video_link")
   in the select list of your conten type (in this case "videos"), Save Configuration
 - Edit the Conten Type ("videos") Autolabel options, and write (or search in Token Browser)
   this token: [video_data:title]
 - Save Content Type Configuration
 - Create a content of type "videos" and write a valid youtube or vimeo url in the field "video_link"
 - Save the content, and the content title is automatically set to video title on vimeo or youtube
