#include <cstdio>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "debug.hpp"

class Net {
  const char * AP_IP = "172.16.0.1";
  const char * AP_NETWORK = "Irrigation Controller";
  const char * AP_PASSWORD = "0501234567";
  IPAddress _localIp;

  public:
    Net();
    bool create_access_point (void);
    bool connect (void);
};
