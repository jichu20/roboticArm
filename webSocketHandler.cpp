#include <Arduino.h>
#include "webSocketHandler.h"
#include <WebSocketsServer.h>
#include "robotic_arm.h"

WebSocketsServer webSocket = WebSocketsServer(81);
// RoboticArm gRoboticArm; // Add this line to define an instance of the RoboticArm class

void startWebSocket(RoboticArm &roboticArm)
{
    webSocket.begin();
    // webSocket.onEvent(onWebSocketEvent);
    // gRoboticArm = roboticArm;
    webSocket.onEvent([&roboticArm](uint8_t num, WStype_t type, uint8_t *payload, size_t length)
                      { onWebSocketEvent(num, type, payload, length, roboticArm); });
    roboticArm.init();
    Serial.println("WebSocket server started.");
}

void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length, RoboticArm &roboticArm)
{
    switch (type)
    {
    case WStype_DISCONNECTED:
        Serial.printf("[%u] Disconnected!\n", num);
        break;
    case WStype_CONNECTED:
    {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %s\n", num, ip.toString().c_str());
        webSocket.sendTXT(num, "Welcome to the WebSocket server!");
        break;
    }
    case WStype_TEXT:
        Serial.printf("[%u] Received text: %s\n", num, payload);
        // Parse the received text message
        String message = String((char *)payload);
        String movement;
        int position;
        int responsePosition;

        // Extract the movement and position from the message
        int separatorIndex = message.indexOf(':');
        if (separatorIndex != -1)
        {
            movement = message.substring(0, separatorIndex);
            position = message.substring(separatorIndex + 1).toInt();
        }

        // Invoke the corresponding method in robotic_arm based on the movement
        Serial.println(movement);
        if (movement == "UP"){
            roboticArm.moveUpVertical(position);
        }
        else if (movement == "DOWN"){
            roboticArm.moveDownVertical(position);
        }
        else if (movement == "LEFT"){
            roboticArm.moveHorizontal(position);
        }
        else if (movement == "RIGHT"){
            roboticArm.moveHorizontal(position);
        }
        else if (movement == "OPEN"){
            roboticArm.openGripper();
        }
        else if (movement == "CLOSE"){
            roboticArm.closeGripper();
        }
        else if (movement == "POS_VERT"){
            roboticArm.setVertical(position);
        }
        else if (movement == "POS_HORI"){
            roboticArm.setHorizontal(position);
        }
        else{
            // Invalid movement, handle accordingly
            Serial.println("Invalid movement");
        }
        // Echo the message back to the client
        webSocket.sendTXT(num, String(responsePosition).c_str());

        break;
    }
}

void handleWebSocket()
{
    webSocket.loop();
}