#ifndef COM_REQUEST__H
#define COM_REQUEST__H

#include <Arduino.h>

class ComMessage {
    int _cmd;
    int _key;
    String _value;
    public:

        static const int CMD_DEBUG = 1;
        static const int CMD_READ = 2;
        static const int CMD_WRITE = 3;
        

        ComMessage (void);
        ComMessage (int cmd, int key, String value);
        void setCommand(int cmd);
        void setKey(int key);
        void setValue(String value);
        int getCommand();
        int getKey();
        String getValue();
};
#endif