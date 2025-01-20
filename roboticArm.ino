// https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-class.html
#include <Arduino.h>
#include "webSocketHandler.h"
#include "httpHandler.h"
#include "wifiHandler.h"
#include "robotic_arm.h"

const int pinHombro = 12;
const int pinCodo = 13;
const int pinMuneca = 14;
const int pinPinza = 15;

RoboticArm roboticArm(pinHombro, pinCodo, pinMuneca, pinPinza); // Add this line to define an instance of the RoboticArm class


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