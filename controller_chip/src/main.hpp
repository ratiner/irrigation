
#include <Arduino.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include "com.hpp"
#include "clock.hpp"
#include "scheduler.hpp"
#include <SchedulerStructures.hpp>
#include <LinkedList.hpp>

void setup();
void initIO();


void loop();

void startValve(int);
void stopValve(int);
void waterPulse();