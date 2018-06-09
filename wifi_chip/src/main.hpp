#include <Arduino.h>
#include "net.hpp"
#include "webServer.hpp"
#include "com.hpp"
#include "debug.hpp"
#include "external.hpp"

void setup();
void loop();
void requestReceived(int cmd, int key, const char * value);