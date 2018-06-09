#ifndef TIMESTAMP_H
#define TIMESTAMP_H
#include <Arduino.h>


const int TS_EQUALS = 0;
const int TS_HIGHER = 1;
const int TS_LOWER = -1;
class TimeStamp {
    
    public:
        byte year;
        byte month;
        byte day;
        byte hour;
        byte min;
        byte sec;
        byte doW;

        int compareTo(TimeStamp& otherTime);

};
#endif
