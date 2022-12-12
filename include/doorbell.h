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
#include "cam-helper.h"
#include "soc/soc.h"            // brownout detector
#include "soc/rtc_cntl_reg.h"   // brownout detector

#define DEVICE_ID           "esp32-cam"
#define DEVICE_NAME         "Doorbell"
#define DEVICE_MANUFACTURER "Ai Thinker"
#define DEVICE_MODEL        "ESP32-CAM"
#define DEVICE_VERSION      "20221210.2130"

#define DOORBELL_PIC_TOPIC "homeassistant/camera/doorbell/snapshot"
#define DOORBELL_TOPIC     "homeassistant/switch/doorbell/ringer"
#define DOORBELL_RING      "ON"
#define DOORBELL_SILENT    "OFF"

//#define FIVEHUNDREDCHARS "ZBKABDUFYTLVUPYJHRAUZSMSHAHZJYTCPDFMNLTHETYETFQPEFSZWSPZZXQNVARAHDDEPEWYHCDGJXHSCWQHXNYHMNARGXAQKLXVQNEYAAQHETPYZMYMNLBJASFHJMXVYTHTPUQHEDLMRYFEMNGRQKDVATJGLBZNTDAAUQZBTZTLNTYYRMWSVNDWNZTWWEYLPWMEKKJTHCSFUDFLMCJXTHBFDXWCLPZWLJVVCXDYHTQRNYQDSPMSYNJPFPXYVZWBPCWECZFARTXLMJYXLGUNQYZWXMRNDLELBKARGDAWUQSBJZSDRVPQZRACBBFAGLQLYJMRBXXLMECVFCHFPUSHEGCLRDJCPUSJRQRXEMRWNPYWTJWNKGTKJBSLVFBFEGSEJSVXQZENNMZXQLYNSJCLKHASNJBYRGHLRDFWPNTPBFMJKTGKFGZMVBWUUUJFZFAMNLXVHRUGFDUXLBYBUCYGDSAKVRQSHGBSNPDSLHNHSPXWSEACDZCW"
//#define TEST_PAYLOAD "The quick brown fox jumped over the fence"

// *********************************************************************************************************************
// *** Must Declare ***


#endif