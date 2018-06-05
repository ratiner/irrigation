#include <cstdio>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "com.hpp"
#include "debug.hpp"
#include "external.hpp"

class WebManager {
    String _req;
    WiFiServer * _server;
    WiFiClient * _client;

   External * _external;
    Com * _com;

    public:
    WebManager(External * external);
    bool start (void);
    bool tryHandleClient(void);
    private:
    void doStaticContent(const String path);
    void doError(int errorCode, const char * message);
    void getRequest();
    char * getContentType(String path);
};
