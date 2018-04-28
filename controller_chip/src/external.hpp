#include <Arduino.h>
#include <SPI.h>
#include <SdFat.h>
#include "debug.hpp"

class External {
    bool _isInit = false;
    SdFat * _SD;
    public:
        External();
        bool init (void);
        bool exists(const char * path);
        File getFile (const char * path);
};
