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

#define DEVICE_ID           "esp32-cam"
#define DEVICE_NAME         "Doorbell"
#define DEVICE_MANUFACTURER "Ai Thinker"
#define DEVICE_MODEL        "ESP32-CAM"
#define DEVICE_VERSION      "20221216.1500"

#endif