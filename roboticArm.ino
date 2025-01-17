// https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-class.html
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include "html.h"

const char* ssid     = "ESP8266-Access-Point";
const char* password = "123456789";

#define LED D0            // Led in NodeMCU at pin GPIO16 (D0).

/* Put IP Address details */
IPAddress local_ip(192,168,4,22);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);

// Create AsyncWebServer object on port 80
ESP8266WebServer server(80);       // Create a webserver object that listens for HTTP request on port 80
WebSocketsServer webSocket(81); 

bool rainbow = false;             // The rainbow effect is turned off on startup

void setup() {
    pinMode(LED, OUTPUT);    // LED pin as output.

    Serial.begin(115200);
    delay(10);
    startWiFi();                 // Start a Wi-Fi access point, and try to connect to some given access points. Then wait for either an AP or STA connection
    startWebSocket();            // Start a WebSocket server
    startServer();               // Start a HTTP server with a file read handler and an upload handler

    // server.on("/", handle_OnConnect);
    // server.on("/up", handlerUp);
    // server.begin();
}

void handle_OnConnect() {
  
    Serial.println("entrando a handle_OnConnect");
    server.send(200, "text/html", SendHTML()); 
}

void handlerUp() {
    digitalWrite(LED_BUILTIN, HIGH); // Turn on the LED
    // delay(1000); // Wait for 1 second
    digitalWrite(LED_BUILTIN, LOW); // Turn off the LED
    Serial.println("Led On");
    // server.send(200, "text/html", SendHTML(LED1status,true)); 
}

void loop() {
    webSocket.loop();                           // constantly check for websocket events
    server.handleClient(); 
}


void startWiFi() { // Start a Wi-Fi access point, and try to connect to some given access points. Then wait for either an AP or STA connection
    Serial.print("Setting soft-AP configuration ... ");
    Serial.println(WiFi.softAPConfig(local_ip, gateway, subnet) ? "Ready" : "Failed!");

    Serial.print("Setting soft-AP ... ");
    Serial.println(WiFi.softAP(ssid, password) ? "Ready" : "Failed!");

    Serial.print("Soft-AP IP address = ");
    Serial.println(WiFi.softAPIP());

    Serial.println(WiFi.localIP());
    Serial.println("\r\n");
}


void startWebSocket() { // Start a WebSocket server
  webSocket.begin();                          // start the websocket server
  webSocket.onEvent(webSocketEvent);          // if there's an incomming websocket message, go to function 'webSocketEvent'
  Serial.println("WebSocket server started.");
}

void startServer() { // Start a HTTP server with a file read handler and an upload handler
    server.on("/", handle_OnConnect);
    server.on("/up", handlerUp);
    server.begin();                             // start the HTTP server
    Serial.println("HTTP server started.");
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) { // When a WebSocket message is received
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

            digitalWrite(LED, HIGH);// turn the LED off.(Note that LOW is the voltage level but actually 
                        //the LED is on; this is because it is acive low on the ESP8266.
            delay(1000);            // wait for 1 second.
            digitalWrite(LED, LOW); // turn the LED on.
            delay(1000); // wait for 1 second.
            break;
    }
}