#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <SD.h>
#include "debug.hpp"

struct NetworkSettings {
    const char * ap_ip;
    const char * ap_network;
    const char * ap_password;
    const char * wifi_network;
    const char * wifi_password;
    bool wifi_enabled;
};

class SettingsClass {
    const char *networkSettingsFile = "/config/network.cfg";

    public:
        struct NetworkSettings getNetworkSettings();
        void setNetworkSettings(String& settings);
};

extern SettingsClass Settings;

#endif
