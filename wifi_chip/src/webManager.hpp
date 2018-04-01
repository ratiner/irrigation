#include <cstdio>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "com.hpp"
#include "debug.hpp"

class WebManager {
    String _req;
    WiFiServer * _server;
    WiFiClient * _client;

    public:
    WebManager();
    bool start (void);
    bool tryHandleClient(void);
    private:
    void doStaticContent(const String path);
    void doError(int errorCode, const char * message);
    void getRequest();
    char * getContentType(String path);
};
