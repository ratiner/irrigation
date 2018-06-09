#ifndef EXTERNAL_H
#define EXTERNAL_H

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "debug.hpp"

class ExternalClass {
    bool _isInit = false;
    public:
        ExternalClass();
        bool init (void);
        bool exists(const char * path);
        File getFile (const char * path);
};

extern ExternalClass External;
#endif