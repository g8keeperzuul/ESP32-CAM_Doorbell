/*
    Contains hardware specific information for the base microcontroller board used. 
*/
#ifndef DOORBELL_H
#define DOORBELL_H

//#include <Arduino.h>  appears to be automatically added by framework specified in platformio.ini
#include <Arduino.h>
#include "wifi-helper.h"
#include "mqtt-helper.h"
#include "log.h"
#include "env.h"


#define DEVICE_ID "esp32-cam"
#define DEVICE_NAME "Doorbell"
#define DEVICE_MANUFACTURER "Ai Thinker"
#define DEVICE_MODEL "ESP32-CAM"
#define DEVICE_VERSION "20221206.2145"

#define DOORBELL_TOPIC "homeassistant/sensor/doorbell/ring"
#define DOORBELL_RING "ON"
#define DOORBELL_SILENT "OFF"

// *********************************************************************************************************************
// *** Must Declare ***

#endif