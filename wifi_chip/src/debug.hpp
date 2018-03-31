#ifndef DEBUG_H
#define DEBUG_H

#include <cstdio>
#include <Arduino.h>

class Debug {
    public:
        static void begin (void);
        static void print (const char * text);
        static void print (String & text);
        static void println (const char * text);
        static void println (String & text);
};
#endif