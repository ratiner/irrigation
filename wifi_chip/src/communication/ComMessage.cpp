#include "ComMessage.hpp"


ComMessage::ComMessage (void)
{
}

ComMessage::ComMessage (int cmd, int key, String value)
{
    _cmd = cmd;
    _key = key;
    _value = value;
}

void ComMessage::setCommand (int cmd)
{
    _cmd = cmd;
}

void ComMessage::setKey (int key)
{
    _key = key;   
}

void ComMessage::setValue (String value)
{
    _value = value;
}

        
int ComMessage::getCommand ()
{
    return _cmd;
}

int ComMessage::getKey ()
{
    return _key;
}

String ComMessage::getValue ()
{
    return _value;
}