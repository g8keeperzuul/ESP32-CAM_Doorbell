/*
    Contains environment specific configuration information.
    This will typically be the same for all applications running within the same environment.

    Rename as env.h
*/
#ifndef LOCAL_ENV_H
#define LOCAL_ENV_H

#define LOCAL_ENV_WIFI_SSID "my-ssid"
#define LOCAL_ENV_WIFI_PASSWORD "my-wifi-password"


#define HA_ACCESS_TOKEN "my-long-lived-access-token"
#define HA_BASE_URL "http://my-homeassistant-host:8123/api" 

// Specify the key (pointing to the media-browser directory) where the snapshot will be uploaded to.
//
// In Home Assistant configuration.yaml:
// homeassistant:
//   media_dirs:    
//     doorbell: /config/www/doorbell-snapshots
//     multimedia: /media 
#define MEDIA_DIRS_KEY "doorbell"
#define MEDIA_DIRS_VAL "/config/www/doorbell-snapshots"

// In Home Assistant configuration.yaml:
// camera:
//   - name: "Doorbell Snapshot"
//     platform: local_file
//     file_path: /doorbell/placeholder.jpg
//
// The entity_id is created from the name
#define CAMERA_ENTITY_ID "camera.doorbell_snapshot"
#define SENSOR_ENTITY_ID "sensor.doorbell_battery"

// Use flash when taking snapshot
#define ENABLE_FLASH false

// https://www.gnu.org/software/libc/manual/html_node/TZ-Variable.html
#define TIMEZONE "UTC0"

// https://www.ntppool.org/zone/@
#define NTP_SERVER "pool.ntp.org

#endif
