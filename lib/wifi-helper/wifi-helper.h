#ifndef WIFI_HELPER_H
#define WIFI_HELPER_H

#include <string>
#include <WiFi.h>
#include "esp_wifi.h"
#include "log.h"

// *********************************************************************************************************************
// *** Must Declare ***
//extern WiFiClient wificlient;

// *** Must Implement ***
void connectWifi(const char *ssid, const char *passphrase);
void printNetworkDetails();
std::string getMAC();
std::string getIP();
int getRSSI();

#endif