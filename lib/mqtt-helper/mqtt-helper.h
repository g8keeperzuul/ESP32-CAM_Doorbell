#ifndef MQTT_HA_HELPER_H
#define MQTT_HA_HELPER_H

#include <AsyncMqttClient.h>
#include "log.h"


// *** MQTT Related Constants ***
#define MQTT_MIN_FREE_MEMORY (25*1024)
#define RETAINED true
#define NOT_RETAINED false
#define QOS_0 0
#define QOS_1 1

// *********************************************************************************************************************
// *** Data Types ***


// *********************************************************************************************************************
// *** Must Declare ***
extern AsyncMqttClient mqttClient;                                            

// *** Must Implement ***
void onMqttConnect(bool sessionPresent);
void onMqttPublish(uint16_t packetId);
void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);

// Provided in library
// Connectivity and basic operations
void initMQTTClient(const IPAddress broker, int port, const char *lwt_topic, const char *payload); 
void connectMQTTBroker(const char *client_id, const char *username, const char *password);
void disconnectMQTTBroker();
void publish(const String &topic, const String &payload);
void publish(const char* topic, const char* payload, unsigned int length);

#endif