#!/bin/bash
# Usage: $0 <doorbell-snapshot.jpg>
# If is expected that his image has already been uploaded to Home Assistant.
# The camera entity will be updated with the provided image. 

source env.sh

# Define camera to display snapshot (in HA configuration.yaml):
# homeassistant:
#      camera:    
#        - name: "Doorbell Snapshot"
#          platform: local_file
#          file_path: /config/www/doorbell-snapshot/placeholder.jpg         


# https://www.home-assistant.io/integrations/local_file/

#MEDIA_FILE="sample_doorbell_image.jpg"
MEDIA_FILE=$1

UPDATE_DOORBELL_CAMERA_SNAPSHOT="{ \"entity_id\": \"camera.doorbell_snapshot\", \"file_path\": \"/config/www/doorbell-snapshots/${MEDIA_FILE}\"}"
  
curl -v -X POST -H "Authorization: Bearer ${HA_ACCESS_TOKEN}" \
     -H "Content-Type: application/json" \
     -d "${UPDATE_DOORBELL_CAMERA_SNAPSHOT}" \
     ${HA_BASE_URL}/services/local_file/update_file_path
