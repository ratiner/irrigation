#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>
#include <Wire.h>
#include <DS3231.h>
#include <TimeStamp.hpp>

class Clock {
    public:
      TimeStamp * getTime();
      void setTime(TimeStamp& stamp);
    private:
        TimeStamp * _now;
        DS3231 DSClock;
};

extern Clock CLOCK;
#endif
