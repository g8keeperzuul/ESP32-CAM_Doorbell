#!/bin/bash
# Usage: $0 <doorbell-snapshot.jpg>
# File will be uploaded via Home Assistant Media Browser (which requires authentication)
# Assumes HA configured with "doorbell" as the media_dirs key (MEDIA_DIR_KEY):
#  homeassistant:
#     media_dirs:
#       doorbell: /config/www/doorbell-snapshots

source env.sh

MEDIA_DIR_KEY="doorbell"
#MEDIA_FILE="sample_doorbell_image.jpg"
MEDIA_FILE=$1

curl -v -X POST -H "Authorization: Bearer ${HA_ACCESS_TOKEN}" \
     -F "media_content_id=media-source://media_source/${MEDIA_DIR_KEY}/." \
     -F "file=@${MEDIA_FILE}" \
     ${HA_BASE_URL}/media_source/local_source/upload
# Response: 200 {"media_content_id":"media-source://media_source/<MEDIA_DIR_KEY>/./<MEDIA_FILE>"}

