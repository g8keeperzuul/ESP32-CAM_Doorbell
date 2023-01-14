#!/bin/bash
# Usage: $0 
# If is expected that his image has already been uploaded to Home Assistant.
# The camera entity will be updated with the provided image. 

source env.sh

# failed attempts:
#PAYLOAD='{"battery_level": 76.5, "battery_mv": 3567, "count": 14}'
#PAYLOAD='{"state": {"battery_level": 76.5, "battery_mv": 3567, "count": 14}, "value_template":"{{ value_json.battery_level | float() }}", "attributes":{"friendly_name": "Doorbell Battery Level 4", "unit_of_measurement": "%" }}'

# /states/camera.doorbell_snapshot
#PAYLOAD='{"file_path": "/config/www/doorbell-snapshots/sample_doorbell_image.jpg", "unique_id": "doorbell_metadata", "attributes":{"friendly_name": "Doorbell", "batt_lvl": 67.5, "batt_mv": 3567, "boot_count": 14 }}'


# Send a single value as sensor state, and the rest of the values with any key. Any unrecognized keys will appear as additional attributes for the sensor.
# These additional attributes can then be extracted as template sensors. 
# /states/sensor.doorbell_battery <== entity_id
# (unique_id ignored, device ignored)
#PAYLOAD='{"state": 86.7, "attributes":{"friendly_name": "Doorbell Battery Level", "unit_of_measurement": "%", "icon": "mdi:battery-50", "batt_mv": 3567, "boot_count": 14 }}'
PAYLOAD='{"state": 76.7, "attributes":{"batt_mv": 3567, "boot_count": 14 }}'

curl -X POST -H "Authorization: Bearer ${HA_ACCESS_TOKEN}" \
       -H "Content-Type: application/json" \
       -d "${PAYLOAD}" \
       ${HA_BASE_URL}/states/sensor.doorbell_battery2

echo "---------------------------------------------------"

curl -X GET -H "Authorization: Bearer ${HA_ACCESS_TOKEN}" \
       -H "Content-Type: application/json" \
       ${HA_BASE_URL}/states/sensor.doorbell_battery2