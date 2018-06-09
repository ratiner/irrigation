#include "com.hpp"

void ComClass::onReceived(ComMessage * req) 
{
    switch(req->getCommand())
    {
        case ComClass::CMD_DEBUG:
        {
            Debug::print("Remote: ");
            Debug::print(req->getValue().c_str());
            transmit(req->getCommand(), req->getKey(), "OK");
            break;
        }
        case ComClass::CMD_READ:
        {
                transmit(req->getCommand(), req->getKey(), "3");
                break;
        }
        case ComClass::CMD_WRITE:
        {
            transmit(req->getCommand(), req->getKey(), "OK");
            break;
        }
    }
}

ComClass COM;