#include "com.hpp"

void ComClass::onReceived(ComMessage * req) 
{
    switch(req->getCommand())
    {
        case ComClass::CMD_READ:
        {
            if(req->getKey() == ComClass::KEY_CLOCK)
            {
                TimeStamp * now = CLOCK.getTime();
                const char * strTime = now->getStr();
                transmit(req->getCommand(), req->getKey(), strTime);
            }
            break;
        }
        case ComClass::CMD_WRITE:
        {
            if(req->getKey() == ComClass::KEY_CLOCK)
            {
                TimeStamp newTime;
                newTime.year =  req->getValue().substring(0, 4).toInt()-2000;
                newTime.month =  req->getValue().substring(5, 7).toInt();
                newTime.day =  req->getValue().substring(8, 10).toInt();
                newTime.hour = req->getValue().substring(11, 13).toInt();
                newTime.min = req->getValue().substring(14, 16).toInt();
                newTime.sec = req->getValue().substring(17, 19).toInt();
                newTime.doW = req->getValue().substring(20,21).toInt()+1;
                CLOCK.setTime(newTime);
                transmit(req->getCommand(), req->getKey(), "OK");
            }

            break;
        }
    }
}

ComClass COM;