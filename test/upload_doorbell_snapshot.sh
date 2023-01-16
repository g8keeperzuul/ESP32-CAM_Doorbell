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

# Format of the HTTP POST request:
#
# Authorization: Bearer <LONG-LIVED TOKEN>
# Content-Length: 16387
# Content-Type: multipart/form-data; boundary=------------------------70280b9e3a69fcd9  
# --------------------------70280b9e3a69fcd9
# Content-Disposition: form-data; name="media_content_id"
# media-source://media_source/doorbell/.
# --------------------------70280b9e3a69fcd9
# Content-Disposition: form-data; name="file"; filename="sample_doorbell_image.jpg"
# Content-Type: image/jpeg
# \xff\xd8\xff\xe0\x00\x10JFIF\x00\......clip
# --------------------------70280b9e3a69fcd9--

curl -v -X POST -H "Authorization: Bearer ${HA_ACCESS_TOKEN}" \
     -F "media_content_id=media-source://media_source/${MEDIA_DIR_KEY}/." \
     -F "file=@${MEDIA_FILE}" \
     ${HA_BASE_URL}/media_source/local_source/upload
# Response: 200 {"media_content_id":"media-source://media_source/<MEDIA_DIR_KEY>/./<MEDIA_FILE>"}

