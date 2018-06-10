#ifndef API_SETTINGS_H
#define API_SETTINGS_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "../debug.hpp"
#include "../settings.hpp"


class APISettings {
    public:
        static void Network_ScanWiFi(WiFiClient&);
        static void Network_GetConfig(WiFiClient&);
    protected: 


};



#endif
