#!/bin/bash

source env.sh

FILENAME=$1

# Home Assistant configuration.yaml:
# homeassistant:
#   media_dirs:    
#     doorbell: /config/www/doorbell-snapshots    <<< IMAGE STORED HERE
#     multimedia: /media 

# if file is stored as a simple "local-file" in /config/www, then no authentication is required
# note the context root of the URL is "local"
curl -X GET --output "/tmp/${FILENAME}" "http://${HA_HOST}/local/doorbell-snapshots/${FILENAME}"

# if file is stored in as a "media-browser" file in /media, then authentication is required
# note the context root of the URL is "media" and the media_dir key is "multimedia"

# Home Assistant configuration.yaml:
# homeassistant:
#   media_dirs:    
#     doorbell: /config/www/doorbell-snapshots
#     multimedia: /media                        <<< IMAGE STORED HERE

#curl -X GET -H "Authorization: Bearer ${HA_ACCESS_TOKEN}" --output "/tmp/${FILENAME}" "http://${HA_HOST}/media/multimedia/${FILENAME}"

# Alternative form with bearer token in URL:
# curl -X GET --output "/tmp/${FILENAME}" "http://${HA_HOST}/media/multimedia/${FILENAME}?authSig=${HA_ACCESS_TOKEN}"

