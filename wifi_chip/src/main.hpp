#include <Arduino.h>
#include "net.hpp"
#include "webManager.hpp"
#include "com.hpp"
#include "debug.hpp"

void setup();
void loop();
void requestReceived(int cmd, int key, const char * value);