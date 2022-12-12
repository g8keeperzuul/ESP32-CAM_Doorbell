#include "doorbell.h"

/*
https://lastminuteengineers.com/esp32-deep-sleep-wakeup-sources/
https://lastminuteengineers.com/esp32-sleep-modes-power-consumption/

https://github.com/moxl-420/ESP32cam-doorbell
https://github.com/ldab/ESP32-CAM-MQTT

https://randomnerdtutorials.com/esp32-cam-ov2640-camera-settings/

https://diyi0t.com/best-battery-for-esp32/
*/

WiFiClient wificlient;  
PubSubClient mqttClient(wificlient);

#define TOUCH_SENSITIVITY_THRESHOLD 40 /* Greater the value, more the sensitivity */

// You can save data in the ESP32’s RTC memory (16kB? SRAM) which is not erased during deep sleep. However, it is erased when the ESP32 is reset.
// To use the data after reboot, store it in RTC memory by defining a global variable with RTC_DATA_ATTR attribute.
RTC_DATA_ATTR int bootCount = 0;
touch_pad_t touchPin;

#ifndef DISABLE_SERIAL_OUTPUT
/*
Method to print the touchpad by which ESP32
has been awaken from sleep
*/
void print_wakeup_touchpad(){
  touchPin = esp_sleep_get_touchpad_wakeup_status();

  Sprint("Touch detected on ");
  switch(touchPin)
  {
    case 0  : Sprintln("GPIO 4"); break;
    case 1  : Sprintln("GPIO 0"); break;
    case 2  : Sprintln("GPIO 2"); break;
    case 3  : Sprintln("GPIO 15"); break;
    case 4  : Sprintln("GPIO 13"); break;
    case 5  : Sprintln("GPIO 12"); break;
    case 6  : Sprintln("GPIO 14"); break;
    case 7  : Sprintln("GPIO 27"); break;
    case 8  : Sprintln("GPIO 33"); break;
    case 9  : Sprintln("GPIO 32"); break;
    default : Sprintln("UNKNOWN!"); break;
  }
}

/*
Method to print the reason by which ESP32
has been awaken from sleep
*/
void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  Sprint("Wakeup caused by ");
  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Sprintln("external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Sprintln("external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Sprintln("timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Sprintln("touchpad"); 
      print_wakeup_touchpad();
      break;
    case ESP_SLEEP_WAKEUP_ULP : Sprintln("ULP program"); break;
    default : Sprintln(wakeup_reason); break;
  }
}
#endif

/*
//get unique deviceId, it contains the MAC address in reverse order
//later also get the device type and Rev

void get_deviceId() {
  uint64_t chipid = ESP.getEfuseMac(); // The chip ID is essentially its MAC address(length: 6 bytes).
  snprintf(deviceId, 23, "%04X%08X", (uint16_t)(chipid >> 32), (uint32_t)chipid);
}

void get_deviceType() {
  snprintf(deviceType, 23, "ESP32", "", "");
}

//  Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());   //ESP.getChipModel() 

//  Serial.printf("This chip has %d cores\n", ESP.getChipCores());
//  Serial.print("Chip ID: "); Serial.println(chipId2);

get_deviceId();
Serial.println(deviceId);
get_deviceType();
Serial.println(deviceType);
*/

void onTouch(){
  //placeholder callback function
  Sprintln("DING DONG!");
}

//Go to sleep now, wake up with touch interrupt
void deep_sleep()
{
  //Setup interrupt on Touch Pad 5 (GPIO12) (cannot use SD card)
  touchAttachInterrupt(T5, onTouch, TOUCH_SENSITIVITY_THRESHOLD);

  //Configure Touchpad as wakeup source
  esp_sleep_enable_touchpad_wakeup();

  Sprintln("Awake for " + String( millis() ) + "ms. Back to sleep...");
  #ifndef DISABLE_SERIAL_OUTPUT
  Serial.flush();
  #endif

  //esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF); // 2.8mA

  esp_deep_sleep_start();
}


void onMqttDisconnect() {
  Sprintln("Disconnected from MQTT");

  if(WiFi.isConnected()) {    
    WiFi.disconnect();
  }
  deep_sleep();
}

void onMqttPublish() {
  Sprintln("Publish successful.");  

  disconnectMQTTBroker();  
  onMqttDisconnect();
}

void onMqttConnect(){

  Sprintln(F("Connected to MQTT broker"));
  
  /*
  if(publish(DOORBELL_TOPIC, DOORBELL_RING)){
    Sprintln("RING! RING!");
  }
  */

  if(initCamera()){
    // take picture
    camera_fb_t *cam_frame_buf = esp_camera_fb_get();

    // send picture
    uint8_t* pic_buf = cam_frame_buf->buf;
    size_t length = cam_frame_buf->len;

    Sprint("Picture size (bytes) = "); Sprintln(length);

/*
    if(publish(DOORBELL_PIC_TOPIC, String(length))){
      delay(100);
      mqttClient.loop();
      delay(100);

      publish("test/flush",String(length)); // flushes first message?
      onMqttPublish();
    }
*/
/*            
    if(publish(DOORBELL_PIC_TOPIC, (uint8_t*)TEST_PAYLOAD, strlen(TEST_PAYLOAD))){
      onMqttPublish();
    }
*/
/*
    if(publish(DOORBELL_PIC_TOPIC, pic_buf, length)){
      onMqttPublish();
    } 
*/    
    if(publishLarge(DOORBELL_PIC_TOPIC, pic_buf, length)){
    //  delay(100);
    //  mqttClient.loop();
      delay(100);
      onMqttPublish();
    } 
/*
    if(mqttClient.publish_P(DOORBELL_PIC_TOPIC, pic_buf, length, NOT_RETAINED)){
      onMqttPublish();
    } 
*/

    Sprintln("Publication of picture NOT successful!");
  }
}

void WiFiEvent(WiFiEvent_t event) {
    Sprint("[WiFi-event] event: "); Sprintln(event);
    switch(event) {

    // 0  SYSTEM_EVENT_WIFI_READY = 0,           /*!< ESP32 WiFi ready */
    // 1  SYSTEM_EVENT_SCAN_DONE,                /*!< ESP32 finish scanning AP */
    // 2  SYSTEM_EVENT_STA_START,                /*!< ESP32 station start */
    // 3  SYSTEM_EVENT_STA_STOP,                 /*!< ESP32 station stop */
    // 4  SYSTEM_EVENT_STA_CONNECTED,            /*!< ESP32 station connected to AP */
    // 5  SYSTEM_EVENT_STA_DISCONNECTED,         /*!< ESP32 station disconnected from AP */
    // 6  SYSTEM_EVENT_STA_AUTHMODE_CHANGE,      /*!< the auth mode of AP connected by ESP32 station changed */
    // 7  SYSTEM_EVENT_STA_GOT_IP,               /*!< ESP32 station got IP from connected AP */
    // 8  SYSTEM_EVENT_STA_LOST_IP,              /*!< ESP32 station lost IP and the IP is reset to 0 */
    // 9  SYSTEM_EVENT_STA_BSS_RSSI_LOW,         /*!< ESP32 station connected BSS rssi goes below threshold */
    // 10 SYSTEM_EVENT_STA_WPS_ER_SUCCESS,       /*!< ESP32 station wps succeeds in enrollee mode */
    // 11 SYSTEM_EVENT_STA_WPS_ER_FAILED,        /*!< ESP32 station wps fails in enrollee mode */
    // 12 SYSTEM_EVENT_STA_WPS_ER_TIMEOUT,       /*!< ESP32 station wps timeout in enrollee mode */
    // 13 SYSTEM_EVENT_STA_WPS_ER_PIN,           /*!< ESP32 station wps pin code in enrollee mode */
    // 14 SYSTEM_EVENT_STA_WPS_ER_PBC_OVERLAP,   /*!< ESP32 station wps overlap in enrollee mode */
    // 15 SYSTEM_EVENT_AP_START,                 /*!< ESP32 soft-AP start */
    // 16 SYSTEM_EVENT_AP_STOP,                  /*!< ESP32 soft-AP stop */
    // 17 SYSTEM_EVENT_AP_STACONNECTED,          /*!< a station connected to ESP32 soft-AP */
    // 18 SYSTEM_EVENT_AP_STADISCONNECTED,       /*!< a station disconnected from ESP32 soft-AP */
    // 19 SYSTEM_EVENT_AP_STAIPASSIGNED,         /*!< ESP32 soft-AP assign an IP to a connected station */
    // 20 SYSTEM_EVENT_AP_PROBEREQRECVED,        /*!< Receive probe request packet in soft-AP interface */
    // 21 SYSTEM_EVENT_ACTION_TX_STATUS,         /*!< Receive status of Action frame transmitted */
    // 22 SYSTEM_EVENT_ROC_DONE,                 /*!< Indicates the completion of Remain-on-Channel operation status */
    // 23 SYSTEM_EVENT_STA_BEACON_TIMEOUT,       /*!< ESP32 station beacon timeout */
    // 24 SYSTEM_EVENT_FTM_REPORT,               /*!< Receive report of FTM procedure */
    // 25 SYSTEM_EVENT_GOT_IP6,                  /*!< ESP32 station or ap or ethernet interface v6IP addr is preferred */
    // 26 SYSTEM_EVENT_ETH_START,                /*!< ESP32 ethernet start */
    // 27 SYSTEM_EVENT_ETH_STOP,                 /*!< ESP32 ethernet stop */
    // 28 SYSTEM_EVENT_ETH_CONNECTED,            /*!< ESP32 ethernet phy link up */
    // 29 SYSTEM_EVENT_ETH_DISCONNECTED,         /*!< ESP32 ethernet phy link down */
    // 30 SYSTEM_EVENT_ETH_GOT_IP,               /*!< ESP32 ethernet got IP from connected AP */
    // 31 SYSTEM_EVENT_ETH_LOST_IP,              /*!< ESP32 ethernet lost IP and the IP is reset to 0 */
    // 32 SYSTEM_EVENT_MAX                       /*!< Number of members in this enum */
      
    case SYSTEM_EVENT_STA_GOT_IP:
        #ifndef DISABLE_SERIAL_OUTPUT
        printNetworkDetails();
        #endif
        if(connectMQTTBroker(DEVICE_ID, LOCAL_ENV_MQTT_USERNAME, LOCAL_ENV_MQTT_PASSWORD, DOORBELL_TOPIC, DOORBELL_SILENT)){
          onMqttConnect();
        }
        break;
    // case SYSTEM_EVENT_STA_DISCONNECTED:
    //     Serial.println("WiFi lost connection");
    //     xTimerStop(mqttReconnectTimer, 0); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
    //     xTimerStart(wifiReconnectTimer, 0);
    //     break;
    }
}


void setup(){

  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector

  #ifndef DISABLE_SERIAL_OUTPUT
  Serial.begin(9600);
  //Serial.setDebugOutput(true);
  delay(1000); //Take some time to open up the Serial Monitor
  #endif

  //Increment boot number and print it every reboot
  ++bootCount;
  Sprintln("Boot number: " + String(bootCount));

  #ifndef DISABLE_SERIAL_OUTPUT
  //Print the wakeup reason for ESP32 and touchpad too
  print_wakeup_reason();
  #endif

  initMQTTClient(LOCAL_ENV_MQTT_BROKER_HOST, LOCAL_ENV_MQTT_BROKER_PORT);
  
  WiFi.onEvent(WiFiEvent);

  connectWifi(LOCAL_ENV_WIFI_SSID, LOCAL_ENV_WIFI_PASSWORD); // --> WiFiEvent --> connectMQTTBroker() --> onMqttConnect() [take photo + publish] --> onMqttPublish() --> disconnectMQTTBroker() --> onMqttDisconnect() --> deep_sleep()

  // this line never reached
}

void loop(){
  // This method will never be called
}