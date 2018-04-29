#include "main.hpp"

void setup() {
    _com = new Com();
    _com->begin();
}





void loop() {
    _com->listen();

    //TODO: Kiril Stuff :)
}