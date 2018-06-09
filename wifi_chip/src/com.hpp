#ifndef COM_H
#define COM_H

#include <Arduino.h>
#include <icom.hpp>
#include "debug.hpp"

class ComClass : public ICom {
    private:
        void onReceived(ComMessage * req);
};

extern ComClass COM;
#endif
