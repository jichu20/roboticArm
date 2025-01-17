#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <WebSocketsServer.h>

extern WebSocketsServer webSocket;

void startWebSocket();
void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);

#endif