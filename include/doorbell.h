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
#define DEVICE_VERSION      "20230102.1500"

// Specified pins should be explicitly pulled-down to LOW with external 10K resistor
// These pins will wake device when any are HIGH
//#define BUTTON_PIN_BITMASK 0x1000 // pin 12 = 2^12 = 0x1000 in hex
#define BUTTON_PIN_BITMASK (1<<12) // same as 2^12; (1<<12 | 1<<13) same as 2^12 + 2^13

//#define DISABLE_BATTERY_TEST 1

// used for battery level test
#define EN_PIN GPIO_NUM_2 // enable battery sample (to be used for digital out)
#define S_PIN GPIO_NUM_13  // battery sample (to be used for analog in)

// Based on 18650 battery
#define MAX_BATT 3740 // millivolts when battery fully charged
#define MIN_BATT 3000 // millivolts when battery considered completely discharged

// Voltage divider used to reduce battery max voltage of 3.74V to <= 3.3V (actually 3.1V)
// voltage divider resistors
#define R1 98400 // ohms
#define R2 20315 // ohms

#define ADJ_MAX_BATT ((MAX_BATT * R1)/(R1 + R2)) // millivolts; max voltage after voltage divider; MUST be <=3.3 
#define ADJ_MIN_BATT ((MIN_BATT * R1)/(R1 + R2)) // millivolts

#endif