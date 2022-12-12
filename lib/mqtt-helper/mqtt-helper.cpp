#include "mqtt-helper.h"

/*
    Using modified PubSubClient library
    https://github.com/mirecta/pubsubclient
    Has simplier, fixed buffer and allows for >64KB buffers to be allocated via MQTT_MAX_PACKET_SIZE (default is 256 bytes)
*/

void initMQTTClient(const IPAddress broker, int port)
{
    Sprint(F("Initalize MQTT client for broker:"));
    Sprint(broker); // IPAddress
    Sprint(":");
    Sprint(port); // int
    Sprint("... ");

    mqttClient.setServer(broker, port);
    //mqttClient.setBufferSize((10*1024)); // NOT SUPPORTED BY modified PubSubClient library; max 64KB, default is 256 bytes MQTT_MAX_PACKET_SIZE
    //mqttClient.setKeepAlive(uint16_t keepAlive);
    //mqttClient.setSocketTimeout(uint16_t timeout);

    // Topic subscription handler
    //mqttClient.setCallback(callback);

    Sprintln(F("Done"));
}


bool connectMQTTBroker(const char *client_id, const char *username, const char *password, const char *lwt_topic, const char *payload)
{  
    Sprintln(F("\nAttempting to connect to MQTT broker... "));
    return mqttClient.connect(client_id, username, password, lwt_topic, QOS_1, RETAINED, payload);
}

void disconnectMQTTBroker(){
    Sprintln(F("\nDisconnecting from MQTT broker... "));
    mqttClient.disconnect();
}

bool publish(const String &topic, const String &payload){
    Sprintln("\nPublishing message: " + topic + " : " + payload);    
    return mqttClient.publish(topic.c_str(), payload.c_str());
}

bool publish(const char* topic, const uint8_t* payload, size_t length){
    Sprint("\nPublishing message: "); Sprint(topic); Sprint(" : ["); Sprint(length); Sprintln("]");    
    return mqttClient.publish(topic, payload, length, NOT_RETAINED);  
}

/* publish binary data over MQTT
* ATTENTION! IN ORDER TO SEND IMAGES >64KB, PATCH buildHeader
* in <Arduino-directory>/libraries/PubSubClient/src/PubSubClient.cpp LIKE THIS
* 
* BEFORE:
* size_t PubSubClient::buildHeader(uint8_t header, uint8_t* buf, uint16_t length)
* ATFER:
* size_t PubSubClient::buildHeader(uint8_t header, uint8_t* buf, uint32_t length)
*
* https://github.com/knolleary/pubsubclient/issues/791#issuecomment-800096719
*/

bool publishLarge(const char* channel, const uint8_t *data, uint32_t len) {

    unsigned long start_ts = millis();

    mqttClient.beginPublish(channel, len, false);
  
    size_t res;
    uint32_t offset = 0;
    uint32_t to_write = len;
    uint32_t buf_len;
    do {
        buf_len = to_write;
        if (buf_len > 64000)
            buf_len = 64000;
   
        res = mqttClient.write(data+offset, buf_len);
        //Sprintln(res);
   
        offset += buf_len;
        to_write -= buf_len;
    } while (res == buf_len && to_write > 0);

    int rc = mqttClient.endPublish();
    //mqttClient.flush();    

    #ifndef DISABLE_SERIAL_OUTPUT
    Serial.printf("Published in MQTT channel %s: (binary data of length %d bytes, %d bytes written in %ld ms)\n", channel, len, len-to_write, millis()-start_ts);
    #endif

    if(rc==1) // success
        return true;
    return false;
}
