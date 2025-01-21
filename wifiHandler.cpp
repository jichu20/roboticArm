#include "wifiHandler.h"
#include <Arduino.h>

const char* ssid     = "ESP8266-Robotic-Arm";
const char* password = "123456789";

/* Put IP Address details */
IPAddress local_ip(192,168,4,22);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);

void startWiFi() {
    Serial.print("Setting soft-AP configuration ... ");
    Serial.println(WiFi.softAPConfig(local_ip, gateway, subnet) ? "Ready" : "Failed!");

    Serial.print("Setting soft-AP ... ");
    Serial.println(WiFi.softAP(ssid, password) ? "Ready" : "Failed!");

    Serial.print("Soft-AP IP address = ");
    Serial.println(WiFi.softAPIP());

    Serial.println(WiFi.localIP());
    Serial.println("\r\n");
}