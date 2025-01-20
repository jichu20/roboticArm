#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <WebSocketsServer.h>
#include "robotic_arm.h"

extern WebSocketsServer webSocket;

void startWebSocket(RoboticArm& roboticArm);
void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length, RoboticArm& roboticArm);

#endif