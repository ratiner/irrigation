#ifndef COM_REQUEST__H
#define COM_REQUEST__H

#include <Arduino.h>

class ComMessage {
    int _cmd;
    int _key;
    String _value;
    public:
        ComMessage (void);
        ComMessage (int cmd, int key, const char *);
        void setCommand(int cmd);
        void setKey(int key);
        void setValue(String value);
        int getCommand();
        int getKey();
        String getValue();
};
#endif