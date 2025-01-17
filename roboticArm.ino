// https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-class.html
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "html.h"

const char* ssid     = "ESP8266-Access-Point";
const char* password = "123456789";

/* Put IP Address details */
// IPAddress local_ip(192,168,1,2);
// IPAddress gateway(192,168,1,1);
IPAddress local_ip(192,168,4,22);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

void setup() {
    Serial.begin(115200);
    delay(10);

    Serial.print("Setting soft-AP configuration ... ");
    Serial.println(WiFi.softAPConfig(local_ip, gateway, subnet) ? "Ready" : "Failed!");

    Serial.print("Setting soft-AP ... ");
    Serial.println(WiFi.softAP(ssid, password) ? "Ready" : "Failed!");

    Serial.print("Soft-AP IP address = ");
    Serial.println(WiFi.softAPIP());



  // Print ESP8266 Local IP Address
    Serial.println(WiFi.localIP());

    server.on("/", handle_OnConnect);
    server.on("/up", handlerUp);
    server.begin();
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
    server.handleClient();
  // put your main code here, to run repeatedly:
    // int device = WiFi.softAPgetStationNum();
    // Serial.printf("Number of devices connected to the AP: %d\n", device);
  
    // Serial.print("Soft-AP IP address = ");
    // Serial.println(WiFi.softAPIP());

    // delay(5000);
}
