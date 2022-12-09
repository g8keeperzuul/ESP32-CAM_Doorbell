#include "doorbell.h"

/*
https://lastminuteengineers.com/esp32-deep-sleep-wakeup-sources/
https://lastminuteengineers.com/esp32-sleep-modes-power-consumption/

https://github.com/moxl-420/ESP32cam-doorbell
https://github.com/ldab/ESP32-CAM-MQTT

https://randomnerdtutorials.com/esp32-cam-ov2640-camera-settings/

https://diyi0t.com/best-battery-for-esp32/
*/

#define TOUCH_SENSITIVITY_THRESHOLD 40 /* Greater the value, more the sensitivity */

// You can save data in the ESP32’s RTC memory (16kB? SRAM) which is not erased during deep sleep. However, it is erased when the ESP32 is reset.
// To use the data after reboot, store it in RTC memory by defining a global variable with RTC_DATA_ATTR attribute.
RTC_DATA_ATTR int bootCount = 0;
touch_pad_t touchPin;

MQTTClient mqttclient((25*1024)); //25KB read & write buffers
WiFiClient wificlient;   

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


void onTouch(){
  //placeholder callback function
  Sprintln("DING DONG!");
}

void deep_sleep()
{
  Sprintln("Awake for " + String( millis() ) + "ms");
  #ifndef DISABLE_SERIAL_OUTPUT
  Serial.flush();
  #endif

  esp_deep_sleep_start();
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

  if(connectWifi(LOCAL_ENV_WIFI_SSID, LOCAL_ENV_WIFI_PASSWORD)){
    #ifndef DISABLE_SERIAL_OUTPUT
    //printNetworkDetails();
    #endif
    initMQTTClient(LOCAL_ENV_MQTT_BROKER_HOST, LOCAL_ENV_MQTT_BROKER_PORT, DOORBELL_TOPIC, DOORBELL_SILENT);
    if(connectMQTTBroker(DEVICE_ID, LOCAL_ENV_MQTT_USERNAME, LOCAL_ENV_MQTT_PASSWORD)){
        // ring doorbell
        if(publish(DOORBELL_TOPIC, DOORBELL_RING)){
          
          if(initCamera()){
            // take picture
            camera_fb_t *cam_frame_buf = esp_camera_fb_get();

            // send picture
            const char* pic_buf = (const char*)(cam_frame_buf->buf);
            size_t length = cam_frame_buf->len;

            //const char* pic_buf = FIVEHUNDREDCHARS;
            //size_t length = 500;
            
            if(publish(DOORBELL_PIC_TOPIC, pic_buf, length)){ // MUST set QOS = 1 to see failures; otherwise all publish attempts are successful even when no image is published to MQTT broker
              Sprintln("Total success!");
            }
            else{
              Sprint("Failed to publish picture. LWMQTT last error = ");              
              Sprintln(mqttclient.lastError()); // 66% of attempts results in LWMQTT_MISSING_OR_WRONG_PACKET = -9
              //ESP.restart();
            }
          }
        }
    }
  }

  // provide time to complete publish before shutdown
  //yield();
  delay(200);
  //mqttclient.loop();

  // --- Prepare for sleep ---

  //Setup interrupt on Touch Pad 5 (GPIO12) (cannot use SD card)
  touchAttachInterrupt(T5, onTouch, TOUCH_SENSITIVITY_THRESHOLD);

  //Configure Touchpad as wakeup source
  esp_sleep_enable_touchpad_wakeup();

  //Go to sleep now, wake up with touch interrupt
  deep_sleep(); // loop from beginning of setup() and this line

  // this line will never be reached
}

void loop(){
  // This method will never be called
}