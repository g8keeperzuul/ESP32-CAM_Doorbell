/*
    Contains hardware specific information for the base microcontroller board used. 
*/
#ifndef DOORBELL_H
#define DOORBELL_H

#include <Arduino.h>
#include "wifi-helper.h"
#include "http-helper.h"
#include "log.h"
#include "env.h"
#include "cam-helper.h"
#include "soc/soc.h"            // brownout detector
#include "soc/rtc_cntl_reg.h"   // brownout detector
#include "time.h"

#define DEVICE_ID           "esp32-cam"
#define DEVICE_NAME         "Doorbell"
#define DEVICE_MANUFACTURER "Ai Thinker"
#define DEVICE_MODEL        "ESP32-CAM"
#define DEVICE_VERSION      "20221222.1900"

// Specified pins should be explicitly pulled-down to LOW with external 10K resistor
// These pins will wake device when any are HIGH
//#define BUTTON_PIN_BITMASK 0x1000 // pin 12 = 2^12 = 0x1000 in hex
#define BUTTON_PIN_BITMASK (1<<12) // same as 2^12; (1<<12 | 1<<13) same as 2^12 + 2^13

#endif