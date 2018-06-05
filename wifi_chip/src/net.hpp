#include <cstdio>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "debug.hpp"
#include "settings.hpp"

class Net {
  IPAddress _localIp;

  public:
    Net();
    bool create_access_point (void);
    bool connect (void);
};
