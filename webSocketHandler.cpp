#include "webSocketHandler.h"
#include <Arduino.h>

WebSocketsServer webSocket = WebSocketsServer(81);

void startWebSocket() {
    webSocket.begin();
    webSocket.onEvent(onWebSocketEvent);
    Serial.println("WebSocket server started.");
}

void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    switch (type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\n", num);
            break;
        case WStype_CONNECTED: {
            IPAddress ip = webSocket.remoteIP(num);
            Serial.printf("[%u] Connected from %s\n", num, ip.toString().c_str());
            webSocket.sendTXT(num, "Welcome to the WebSocket server!");
            break;
        }
        case WStype_TEXT:
            Serial.printf("[%u] Received text: %s\n", num, payload);
            // Echo the message back to the client
            webSocket.sendTXT(num, payload);
            break;
    }
}

void handleWebSocket() {
    webSocket.loop();
}