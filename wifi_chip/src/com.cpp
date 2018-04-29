#include "com.hpp"

void Com::onReceived(ComMessage * req) 
{
    switch(req->getCommand())
    {
        case Com::CMD_DEBUG:
        {
            Debug::print("Remote: ");
            Debug::print(req->getValue().c_str());
            transmit(req->getCommand(), req->getKey(), "OK");
            break;
        }
        case Com::CMD_READ:
        {
                transmit(req->getCommand(), req->getKey(), "3");
                break;
        }
        case Com::CMD_WRITE:
        {
            transmit(req->getCommand(), req->getKey(), "OK");
            break;
        }
    }
}