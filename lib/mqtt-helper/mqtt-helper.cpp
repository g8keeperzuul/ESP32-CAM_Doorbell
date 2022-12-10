#include "mqtt-helper.h"

AsyncMqttClient mqttClient;

void initMQTTClient(const IPAddress broker, int port, const char *lwt_topic, const char *payload)
{
    Sprint(F("Initalize MQTT client for broker:"));
    Sprint(broker); // IPAddress
    Sprint(":");
    Sprint(port); // int
    Sprint("... ");

    mqttClient.setServer(broker, port);
    mqttClient.setWill(lwt_topic, QOS_1, RETAINED, payload);  

    mqttClient.onConnect(onMqttConnect);
    mqttClient.onPublish(onMqttPublish);
    mqttClient.onDisconnect(onMqttDisconnect);

    Sprintln(F("Done"));
}


void connectMQTTBroker(const char *client_id, const char *username, const char *password)
{  
    Sprintln(F("\nAttempting to connect to MQTT broker... "));
    mqttClient.setClientId(client_id);
    mqttClient.setCredentials(username, password);
    mqttClient.connect();
}

void disconnectMQTTBroker(){
    Sprintln(F("\nDisconnecting from MQTT broker... "));
    mqttClient.disconnect();
}

void publish(const String &topic, const String &payload){
    Sprintln("\nPublishing message: " + topic + " : " + payload);    
    uint16_t packetIdPub = mqttClient.publish(topic.c_str(), QOS_0, NOT_RETAINED, payload.c_str());
    Sprint("Publishing at QoS 0, packetId: "); Sprintln(packetIdPub);  
}

void publish(const char* topic, const char* payload, unsigned int length){
    Sprint("\nPublishing message: "); Sprint(topic); Sprint(" : ["); Sprint(length); Sprintln("]");    
    uint16_t packetIdPub = mqttClient.publish(topic, QOS_1, NOT_RETAINED, payload, length);
    Sprint("Publishing at QoS 1, packetId: "); Sprintln(packetIdPub);    
}
