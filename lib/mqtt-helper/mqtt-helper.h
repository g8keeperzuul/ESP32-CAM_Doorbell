#ifndef MQTT_HA_HELPER_H
#define MQTT_HA_HELPER_H

#include <WiFi.h> // for WiFiClient
#include <MQTT.h>
#include <vector>
#include <queue>
#include <string>
#include "log.h"

// Not used by this library, but meant to be used by the users of this library between calls to connectMQTTBroker()
#define MQTT_ATTEMPT_COOLDOWN 10000 // milliseconds between MQTT broker connection attempts

// *** MQTT Related Constants ***
#define RETAINED true
#define NOT_RETAINED false
// https://github.com/256dpi/arduino-mqtt/blob/master/src/lwmqtt/lwmqtt.h#L66
#define QOS_0 0
#define QOS_1 1

// *** MQTT Related Constants ***

// *********************************************************************************************************************
// *** Data Types ***


// *********************************************************************************************************************
// *** Must Declare ***
extern MQTTClient mqttclient;
extern WiFiClient wificlient;                                                 

// *** Must Implement ***

// Provided in library
// Connectivity and basic operations
void initMQTTClient(const IPAddress broker, int port, const char *lwt_topic, const char *payload); 
bool connectMQTTBroker(const char *client_id, const char *username, const char *password);
void publish(const String &topic, const String &payload);

#endif