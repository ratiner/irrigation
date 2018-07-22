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
            else if(req->getKey() == ComClass::KEY_STATUS)
            {
                LinkedList<Program*> * progs = Scheduler.getPrograms();
                Program * p = progs->get(0);
                String str = String(p->active);
                transmit(req->getCommand(), req->getKey(), str.c_str());
            }
            break;
        }
        case ComClass::CMD_WRITE:
        {
            if(req->getKey() == ComClass::KEY_CLOCK)
            {
                TimeStamp newTime;
                newTime.fromStr(req->getValue().c_str());
                CLOCK.setTime(newTime);
                transmit(req->getCommand(), req->getKey(), "OK");
            }

            break;
        }
        case ComClass::CMD_MANUAL:
        {
           // LinkedList<Program*> * progs = Scheduler.getPrograms();
           // Program * p = progs->get(0);

            if(req->getKey() == ComClass::KEY_OPEN)
            {
                digitalWrite(13,HIGH);
                digitalWrite(8, HIGH);
                digitalWrite(9, LOW);
                delay(100);
                digitalWrite(8, LOW);
                digitalWrite(9, LOW);
               
                //p->active = 1;
                //String str = String(p->active);

            }
            else if(req->getKey() == ComClass::KEY_CLOSE)
            {
                digitalWrite(13,LOW);
                digitalWrite(8, LOW);
                digitalWrite(9, HIGH);
                delay(100);
                digitalWrite(8, LOW);
                digitalWrite(9, LOW);
                //p->active = 0;
            }

            transmit(req->getCommand(), req->getKey(), "OK");
            break;

        }
    }

}

ComClass COM;