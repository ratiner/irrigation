#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "webRequest.hpp"
#include "debug.hpp"


enum HTTPClientStatus { HC_NONE, HC_WAIT_READ, HC_WAIT_CLOSE };
#define HTTP_MAX_SEND_WAIT 6000 //ms to wait for data chunk to be ACKed
#define HTTP_MAX_DATA_WAIT 5000 //ms to wait for the client to send the request
#define HTTP_MAX_CLOSE_WAIT 6000 //ms to wait for the client to close the connection

class WebServer {
    WebRequest * _req;
    WiFiServer _server;
    WiFiClient  _client;
    HTTPClientStatus _currentStatus;
    unsigned long _statusChange;

    public:
    WebServer();
    bool begin (void);
    void handleClient(void);

    protected: 
    bool _close(void);
    bool _parseRequest(void);
    String urlDecode(const String&);
};



#endif
