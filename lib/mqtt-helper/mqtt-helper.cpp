#include "mqtt-helper.h"

void initMQTTClient(const IPAddress broker, int port, const char *lwt_topic, const char *payload)
{
  Sprint(F("Initalize MQTT client for broker:"));
  Sprint(broker); // IPAddress
  Sprint(":");
  Sprint(port); // int
  Sprint("... ");

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported
  // by Arduino. You need to set the IP address directly.
  // https://github.com/256dpi/arduino-mqtt/blob/master/src/MQTTClient.h#L101
  mqttclient.begin(broker, port, wificlient);

  // https://github.com/256dpi/arduino-mqtt/blob/master/src/MQTTClient.cpp#L199
  //mqttclient.onMessage(messageReceived);

  //mqttclient.setTimeout(5000);

  mqttclient.setWill(lwt_topic, payload, RETAINED, QOS_1);

  Sprintln(F("Done"));
}

// Returns TRUE if connected to MQTT broker
bool connectMQTTBroker(const char *client_id, const char *username, const char *password)
{  
  if(!mqttclient.connected())
  {
    Sprint(F("\nAttempting to connect to MQTT broker... "));
    if(mqttclient.connect(client_id, username, password)){
        Sprintln(F("Connected!"));
        return true;
    }
    else{
        Sprintln(F("Failed!"));
        return false;
    }
  }
  else {
    return true;
  }
}

bool publish(const String &topic, const String &payload){
    Sprintln("\nPublishing message: " + topic + " : " + payload);    
    return mqttclient.publish(topic, payload, NOT_RETAINED, QOS_0);
}

bool publish(const char* topic, const char* payload, unsigned int length){
    Sprint("\nPublishing message: "); Sprint(topic); Sprint(" : ["); Sprint(length); Sprintln("]");
    return mqttclient.publish(topic, payload, length, NOT_RETAINED, QOS_1);
}
