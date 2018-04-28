#include "com.hpp"


void Com::begin(void)
{
    Serial.begin(9600);
    _buffer = "";
}

void Com::listen() {
    if(Serial.available())
    {
        ComMessage * msg = receive(); 
        if(!msg)  
            return;


        switch(msg->getCommand())
        {
            case ComMessage::CMD_DEBUG:
            {
                Debug::print("Remote: ");
                Debug::print(msg->getValue().c_str());
                transmit(msg->getCommand(), msg->getKey(), "OK");
                break;
            }
            case ComMessage::CMD_READ:
            {
                 transmit(msg->getCommand(), msg->getKey(), "3");
                 break;
            }
            case ComMessage::CMD_WRITE:
            {
                transmit(msg->getCommand(), msg->getKey(), "OK");
                break;
            }
        }
    }
}

ComMessage * Com::send (int cmd, int key, const char * value)
{
    transmit(cmd, key, value);
    return receive();
}


///PRIVATE FUNCTIONS

void Com::transmit(int cmd, int key, const char * value) 
{
    Serial.print(Com::_start);
    Serial.print(cmd);
    Serial.print(Com::_split);
    Serial.print(key);
    Serial.print(Com::_split);
    Serial.print(value);
    Serial.print(Com::_end);
}

ComMessage * Com::receive () 
{
    int timer = 0;
    while(!Serial.available()) {
        if(timer >= _timeout)
            return NULL;
        delay(200);
        timer += 200;
    }

    while(Serial.available())
    {
        _buffer += (char)Serial.read();
    }
    
    int idxStart = _buffer.indexOf(_start);
    int idxEnd = _buffer.indexOf(_end);
    int idxSplit;

    if(idxEnd > -1) 
    {
         String cmd, key, value;


        _buffer = _buffer.substring(idxStart+_start.length());
        idxSplit = _buffer.indexOf(_split);
        cmd = _buffer.substring(0, idxSplit);
        _buffer = _buffer.substring(idxSplit + _split.length());
        idxSplit = _buffer.indexOf(_split);
        key = _buffer.substring(0, idxSplit);
        _buffer = _buffer.substring(idxSplit + _split.length());
        idxEnd = _buffer.indexOf(_end);
        value = _buffer.substring(0, idxEnd);
        _buffer = _buffer.substring(idxEnd+_end.length());
        
      //  Debug::println("before call");
     //   _receivedCallback(cmd.toInt(), key.toInt(), value.c_str());
    
        return new ComMessage(cmd.toInt(), key.toInt(), value);
    }
    
    return NULL;
}


void Com::setReceiver(void (*callback)(int cmd, int key, const char * value)) {
    Com::_receivedCallback = callback;
}