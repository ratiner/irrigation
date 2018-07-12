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

/*
struct Counter {
    byte ports[2];
};

struct Valve {
    byte id;
    byte ports[2];
    byte mode;
};

struct IOSettings {
    Counter main_counter;
    int valves_count;
    Valve * valves;
};


struct Program {
    
}
*/


class SettingsClass {
    const char *networkSettingsFile = "/config/network.cfg";
    const char *ioSettingsFile = "/config/io.cfg";
    const char *programSettingsFolder = "/config/programs/";

    public:
        struct NetworkSettings getNetworkSettings();
        void setNetworkSettings(String& settings);
        File & getIOSettings();
        void setIOSettings(String& settings);
        byte getPrograms();
        File & getProgram(String & id);
        void setProgram(byte id, String& settings);

};

extern SettingsClass Settings;

#endif
