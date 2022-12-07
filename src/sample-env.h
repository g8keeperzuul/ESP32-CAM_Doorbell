/*
    Contains environment specific configuration information.
    This will typically be the same for all applications running within the same environment.

    Rename as env.h
*/
#ifndef LOCAL_ENV_H
#define LOCAL_ENV_H

#define LOCAL_ENV_WIFI_SSID "my-ssid"
#define LOCAL_ENV_WIFI_PASSWORD "my-wifi-password"

#define LOCAL_ENV_MQTT_USERNAME "this-device"
#define LOCAL_ENV_MQTT_PASSWORD "my-mqtt-password"
#define LOCAL_ENV_MQTT_BROKER_HOST IPAddress(10,0,0,2)
#define LOCAL_ENV_MQTT_BROKER_PORT 1883

#endif
