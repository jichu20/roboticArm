// https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-class.html
#include <Arduino.h>
#include "webSocketHandler.h"
#include "httpHandler.h"
#include "wifiHandler.h"

void setup() {

    Serial.begin(115200);
    delay(10);
    startWiFi();                 // Start a Wi-Fi access point, and try to connect to some given access points. Then wait for either an AP or STA connection
    startWebSocket();            // Start a WebSocket server
    startHttpServer();               // Start a HTTP server with a file read handler and an upload handler

}

void loop() {
    // handleWebSocket(); // constantly check for websocket events
    webSocket.loop(); // constantly check for websocket events
    server.handleClient();
}