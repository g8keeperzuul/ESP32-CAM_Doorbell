//#include <Arduino.h>
#include "wifi-helper.h"

WiFiClient wificlient;   

/*
  Attempt to connect to wireless network ONCE, and wait ATTEMPT_DURATION (milliseconds) for 
  connection to be established. 
*/
void connectWifi(const char *ssid, const char *passphrase)
{
  Sprint(F("Attempting to connect to wireless network \""));
  Sprint(ssid);
  Sprintln("\"... ");

  // Set WiFi mode to station (as opposed to AP or AP_STA)
  WiFi.mode(WIFI_STA);
  // WiFI.begin([ssid], [passkey]) initiates a WiFI connection
  // to the stated [ssid], using the [passkey] as a WPA, WPA2,
  // or WEP passphrase.    
  WiFi.begin(ssid, passphrase);   
}

void printNetworkDetails()
{
  // SSID of the network you're attached to
  Sprint(F("SSID: "));
  Sprintln(WiFi.SSID()); // String

  // Hostname of this device
  Sprint(F("Hostname: "));
  Sprintln(WiFi.getHostname()); // char*

  Sprint(F("IP: "));
  Sprintln(WiFi.localIP()); // IPAddress

  Sprint(F("Subnet mask: "));
  Sprintln(WiFi.subnetMask()); // IPAddress

  Sprint(F("Broadcast IP: "));
  Sprintln(WiFi.broadcastIP()); // IPAddress

  Sprint(F("Gateway IP: "));
  Sprintln(WiFi.gatewayIP()); // IPAddress  

  Sprint(F("MAC: "));
  Sprintln(WiFi.macAddress());

  // MAC address of the router you're attached to
  Sprint("BSSID: ");
  Sprintln(WiFi.BSSIDstr()); // String

  // Received signal strength
  Sprint(F("RSSI: "));
  Sprintln(WiFi.RSSI()); // int8_t

  // Wifi password
  // Serial.print("PSK: ");
  // Serial.println(WiFi.psk()); // String

  // Encryption type:
  // byte encryption = WiFi.encryptionType();
  // Serial.print("Encryption Type: ");
  // Serial.println(encryption, HEX);

  // First DNS
  Sprint(F("DNS IP: "));
  Sprintln(WiFi.dnsIP(0)); // IPAddress

  Sprintln("");
}

std::string getMAC(){
  return std::string(WiFi.macAddress().c_str());
}

std::string getIP(){
  return std::string(WiFi.localIP().toString().c_str());
}

int getRSSI(){
  return WiFi.RSSI();
}