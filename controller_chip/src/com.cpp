#include "com.hpp"

void Com::onReceived(ComMessage * req) 
{
    switch(req->getCommand())
    {
        case Com::CMD_READ:
        {
            break;
        }
        case Com::CMD_WRITE:
        {
            break;
        }
    }
}