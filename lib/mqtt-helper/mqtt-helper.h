#ifndef MQTT_HA_HELPER_H
#define MQTT_HA_HELPER_H

#include <PubSubClient.h>
#include "log.h"


// *** MQTT Related Constants ***
#define RETAINED true
#define NOT_RETAINED false
#define QOS_0 MQTTQOS0
#define QOS_1 MQTTQOS1

// *** PubSubClient Related Constants ***
//#define MQTT_MAX_TRANSFER_SIZE (5*1024)
//#define MQTT_MAX_PACKET_SIZE (5*1024)

// *********************************************************************************************************************
// *** Data Types ***


// *********************************************************************************************************************
// *** Must Declare ***
extern PubSubClient mqttClient;                                            

// *** Must Implement ***

// Provided in library
// Connectivity and basic operations
void initMQTTClient(const IPAddress broker, int port); 
bool connectMQTTBroker(const char *client_id, const char *username, const char *password, const char *lwt_topic, const char *payload);
void disconnectMQTTBroker();
bool publish(const String &topic, const String &payload);
bool publish(const char* topic, const uint8_t* payload, size_t length);
bool publishLarge(const char* channel, const uint8_t *data, uint32_t len);

#endif