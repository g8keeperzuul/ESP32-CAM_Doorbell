#!/bin/bash

source env.sh

curl -X POST -H "Authorization: Bearer ${HA_ACCESS_TOKEN}" \
  -H "Content-Type: application/json" \
  -d '{"state": "on", "attributes":{"friendly_name":"Doorbell Ringer", "icon":"mdi:doorbell-video"}}' \  
  ${HA_BASE_URL}/states/switch.doorbell

  #-d '{"state": "on"}' \