#ifndef HTTPHANDLER_H
#define HTTPHANDLER_H

#include <ESP8266WebServer.h>

extern ESP8266WebServer server;

void startHttpServer();
void handleRoot();
void handleNotFound();
void sendHTML();

#endif