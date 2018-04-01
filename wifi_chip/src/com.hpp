#ifndef COM_H
#define COM_H

#include <cstdio>
#include <Arduino.h>

class Com {
    static const char * const  _start;
    static const char * const _split;
    static const char * const _end;
    public:
        static void begin (void);
        static void set (int cmd, int key, const char * value);
        static void get (int cmd, int key);
       
};
#endif