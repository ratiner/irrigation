#include "com.hpp"


void Com::begin(void)
{
   // Serial.begin(9600);
    _buffer = "";
}

void Com::listen(void)
{
    char c;
    if(Serial.available())
    {
        c = Serial.read();
        while(c > -1)
        {
            _buffer += c;
            c= Serial.read();
        }
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
        key = _buffer.substring(0, idxSplit);
        _buffer = _buffer.substring(idxSplit + _split.length());
        value = _buffer.substring(0, idxSplit);
        idxEnd = _buffer.indexOf(_end);
        _buffer = _buffer.substring(idxEnd+_end.length());

        
       // Serial.println("CMD:" + cmd);
       // Serial.println("key:" + key);
        //Serial.println("value:" + value);
        if(cmd == "1")
        {
            digitalWrite(4, value.toInt());
        }
    }
}

void Com::set (int cmd, int key, int value) 
{
    Serial.print(_start);
    Serial.write(cmd);
    Serial.write(key);
    Serial.write(value);
    Serial.print(_end);
}


void Com::set (int cmd, int key, const char * value) 
{

}

void Com::get (int cmd, int key) 
{

}