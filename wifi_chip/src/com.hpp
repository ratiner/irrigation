#ifndef COM_H
#define COM_H

#include <Arduino.h>
#include "communication/ComMessage.hpp"
#include "debug.hpp";

class Com {
    const int _timeout = 2000; //ms
    const String  _start = ":::";
    const String _split = ",,,";
    const String _end = ";;;";
    String _buffer;

    void (*_receivedCallback)(int cmd, int key, const char * value);

    public:
        void begin (void);
        void listen(void);
        ComMessage * send (int cmd, int key, const char * value);
        void setReceiver(void (*callback)(int cmd, int key, const char * value));
    private:
        ComMessage * receive ();
        void transmit(int cmd, int key, const char * value);
       
};
#endif