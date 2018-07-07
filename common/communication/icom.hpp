#ifndef ICOM_H
#define ICOM_H

#include <Arduino.h>
#include "ComMessage.hpp"

class ICom {
    const int _timeout = 2000; //ms
    const String  _start = ":::";
    const String _split = ",,,";
    const String _end = ";;;";
    String _buffer;

    void (*_receivedCallback)(int cmd, int key, const char * value);

    public:
        static const int CMD_DEBUG = 1;
        static const int CMD_READ = 2;
        static const int CMD_WRITE = 3;
        static const int KEY_CLOCK = 0;

        void begin (void);
        void listen(void);
        ComMessage * send (int cmd, int key, const char * value);
        void setReceiver(void (*callback)(int cmd, int key, const char * value));
    protected:
        ComMessage * receive ();
        virtual void onReceived(ComMessage * req) = 0;
        void transmit(int cmd, int key, const char * value);
       
};
#endif
