#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <SD.h>
#include "debug.hpp"


struct NetworkSettings {
    String ap_ip;
    String ap_network;
    String ap_password;
    String wifi_network;
    String wifi_password;
    bool wifi_enabled;
};

class Settings {
    const char *networkSettingsFile = "/config/network.cfg";

    public:
        struct NetworkSettings getNetworkSettings();
};
#endif
