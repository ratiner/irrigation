#include "icom.hpp"

void ICom::begin(void)
{
    Serial.begin(9600);

    _buffer = "";
    _response = new ComMessage();
}

void ICom::listen()
{
    if (Serial.available())
    {
        receive();
        if (_response->getCommand() == -9)
            return;
        onReceived(_response);
    }
}

ComMessage * ICom::send(int cmd, int key, const char *value)
{
    int retry = 1;
    while(retry < 5) 
    {
        transmit(cmd, key, value);
        receive();
        if(_response->getValue() == NULL || _response->getValue() == "")
        {
            retry++;
            delay(1000);
        }
        else {
            retry = 99;
            break;
        }
    }
    return _response;
}

ComMessage * ICom::send(int cmd, int key, File &value)
{
    int retry = 1;
    while(retry < 5) 
    {
        transmit(cmd, key, value);
        receive();
        if(_response->getValue() == NULL || _response->getValue() == "")
        {
            retry++;
            delay(1000);
        }
        else {
            retry = 99;
            break;
        }
    }
    return _response;
}

///PRIVATE FUNCTIONS

void ICom::transmit(int cmd, int key, const char *value)
{
     Serial.print(ICom::_start);
    Serial.print(cmd);
    Serial.print(ICom::_split);
    Serial.print(key);
    Serial.print(ICom::_split);
    Serial.print(value);
    Serial.print(ICom::_end);
    
    /*
    char str[4];
    snprintf(str, 5, "%02d%02d", cmd, key);

    Serial.print(ICom::_start);
    Serial.print(str);
    // Serial.print(ICom::_split);
    // Serial.print(key);
    // Serial.print(ICom::_split);
    Serial.print(value);
    Serial.print(ICom::_end);
    */
}

void ICom::transmit(int cmd, int key, File &value)
{
    int i;
    Serial.print(ICom::_start);
    Serial.print(cmd);
    Serial.print(ICom::_split);
    Serial.print(key);
    Serial.print(ICom::_split);
    
    while (value.available())
    {
        if (i++ > 10)
        {
            delay(100);
            i = 0;
        }
        char ch = value.read();
        Serial.write(ch);
    }

    Serial.print(ICom::_end);

    /*
    char str[4];
    snprintf(str, 5, "%02d%02d", cmd, key);
    byte i = 0;
    Serial.print(ICom::_start);
    Serial.print(str);
    while (value.available())
    {
        if (i++ > 20)
        {
            delay(100);
            i = 0;
        }
        char ch = value.read();
        if (ch == ICom::_start || ch == ICom::_end)
            Serial.write(ch); //double for escape
        Serial.write(ch);
    }
    Serial.print(ICom::_end);
    */
}

void ICom::receive()
{
    _response->setValue("");
    _response->setCommand(-9);
    _response->setKey(-9);

    String cmd;
    String key;
    String value;

    int timer = 0;
    while (true)
    {
        while (Serial.available())
        {
            _buffer += (char)Serial.read();
        }

        int idxStart = _buffer.indexOf(_start);
        int idxEnd = _buffer.indexOf(_end);
        int idxSplit;

        if (idxEnd > -1)
        {
            _buffer = _buffer.substring(idxStart + _start.length());
            idxSplit = _buffer.indexOf(_split);
            cmd = _buffer.substring(0, idxSplit);
            _buffer = _buffer.substring(idxSplit + _split.length());
            idxSplit = _buffer.indexOf(_split);
            key = _buffer.substring(0, idxSplit);
            _buffer = _buffer.substring(idxSplit + _split.length());
            idxEnd = _buffer.indexOf(_end);
            value = _buffer.substring(0, idxEnd);
            _buffer = _buffer.substring(idxEnd + _end.length());

            //  Debug::println("before call");
            //   _receivedCallback(cmd.toInt(), key.toInt(), value.c_str());
            _response->setCommand(cmd.toInt());
            _response->setKey(key.toInt());
            _response->setValue(value);
            return;
        }

        if (timer >= _timeout)
            return;
        delay(200);
        timer += 200;
    }

  

    /*
    char c;
    int timer = 0;
    bool startFlag = false;
    bool endFlag = false;
    
    while (true)
    {
        while (Serial.available())
        {
            c = Serial.read();
            if (!startFlag && c == _start)
            {
                startFlag = true;
                continue;
            }
            else if (startFlag && c != _start)
            {
                _buffer = ""; //clear buffer.
                startFlag = false;
            }
            else if (startFlag)
            {
                startFlag = false; //\t is part of content
            }
            else if (!endFlag && c == _end)
            {
                endFlag = true;
                continue;
            }
            else if (endFlag && c != _end)
            {
                break;
            }
            else if (endFlag)
            {
                endFlag = false; // \n is part of content
            }

            if (c >= 32 && c <= 126 || c == _start || c == _end)
            {
                _buffer += c;
            }
            c = NULL;
        }

       
        if (endFlag)
        {
            String cmd, key, value;
            cmd = _buffer.substring(0, 2);
            key = _buffer.substring(2, 4);
            value = _buffer.substring(4);

            _buffer = "";
            endFlag = false;
            startFlag = false;

            if(cmd.toInt() > 0 && key.toInt() > 0)
                return new ComMessage(cmd.toInt(), key.toInt(), value);
            else
                return NULL; //err
        }

        if (timer >= _timeout)
            return NULL;
        delay(200);
        timer += 200;
    }*/
}

void ICom::setReceiver(void (*callback)(int cmd, int key, const char *value))
{
    ICom::_receivedCallback = callback;
}

String &ICom::getBuffer()
{
    return _buffer;
}