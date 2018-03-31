#include <cstdio>
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "debug.hpp"

class External {
    bool _isInit = false;
    public:
        External();
        bool init (void);
        bool exists(const char * path);
        File getFile (const char * path);
};
