#ifndef HTTP_HELPER_H
#define HTTP_HELPER_H

#include <HTTPClient.h>
#include <WiFi.h>
#include "log.h"

// *********************************************************************************************************************
// *** Must Declare ***
extern HTTPClient httpclient;
extern WiFiClient wificlient;

// *********************************************************************************************************************
// *** Must Implement ***
bool postJson(const char* bearer_token, const char* url, const char* payload);
bool postBinary(const char* bearer_token, const char* url, String media_dirs_key, String filename, uint8_t* payload, size_t payload_size);

#endif