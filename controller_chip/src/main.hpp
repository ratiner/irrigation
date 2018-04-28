
#include <Arduino.h>
#include <Wire.h>
#include "com.hpp"
#include "debug.hpp"
#include "external.hpp"

Com * _com;

void setup();
void loop();
void requestEvent();
void receiveEvent(int iData);