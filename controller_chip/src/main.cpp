#include "main.hpp"

String cmd;

void setup() {
    // put your setup code here, to run once:
    _com = new Com();
    _com->begin();
    


    pinMode(4, OUTPUT);
    pinMode(12, INPUT);
    digitalWrite(4, HIGH);
}

void loop() {
    _com->listen();

    
}