#ifndef API_SCHED_H
#define API_SCHED_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "../com.hpp"
#include "../debug.hpp"
#include "../settings.hpp"


class APIScheduler {
    public:
        static void Programs_Get(WiFiClient&);
        static void Program_Get(String &, WiFiClient&);
        static void Program_Set(String &, WiFiClient &, String&);
    protected: 


};



#endif
