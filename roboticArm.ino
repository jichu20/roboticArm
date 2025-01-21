// https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-class.html
#include <Arduino.h>
#include "webSocketHandler.h"
#include "httpHandler.h"
#include "wifiHandler.h"
#include "robotic_arm.h"

const int pinBase = 5; // D1
const int pinHombro = 4; // D2
const int pinCodo = 0; // D3
const int pinPinza = 2; // D4

RoboticArm roboticArm(pinHombro, pinCodo, pinBase, pinPinza); // Add this line to define an instance of the RoboticArm class


void setup() {
    Serial.begin(115200);
    delay(10);
    startWiFi();                 // Start a Wi-Fi access point, and try to connect to some given access points. Then wait for either an AP or STA connection
    roboticArm.init();
    startWebSocket(roboticArm);            // Start a WebSocket server
    startHttpServer();               // Start a HTTP server with a file read handler and an upload handler
}

void loop() {
    webSocket.loop(); // constantly check for websocket events
    server.handleClient();
}