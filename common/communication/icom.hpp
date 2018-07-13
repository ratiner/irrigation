#ifndef ICOM_H
#define ICOM_H

#include <Arduino.h>
#include <SD.h>
#include "ComMessage.hpp"

class ICom {
    const int _timeout = 3000; //ms
    const String  _start = ":::";
    const String _split = ",,,";
    const String _end = ";;;";
    
    //const char  _start = '\t';
    //const String _split = ",,,";
    //const char _end = '\n';
    String _buffer;

    void (*_receivedCallback)(int cmd, int key, const char * value);

    public:
        static const int CMD_DEBUG = 1;
        static const int CMD_READ = 2;
        static const int CMD_WRITE = 3;
        static const int KEY_CLOCK = 1;
        static const int KEY_IO = 2;
        static const int KEY_PROGRAM = 3;

        void begin (void);
        void listen(void);
        ComMessage * send (int cmd, int key, const char * value);
        ComMessage * send (int cmd, int key, File & value);

        void setReceiver(void (*callback)(int cmd, int key, const char * value));
        String & getBuffer();
    protected:
        ComMessage * receive ();
        virtual void onReceived(ComMessage * req) = 0;
        void transmit(int cmd, int key, const char * value);
        void transmit(int cmd, int key, File & value);
       
};
#endif
