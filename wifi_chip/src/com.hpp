#ifndef COM_H
#define COM_H

#include <Arduino.h>
#include <icom.hpp>
#include "debug.hpp"
#include "settings.hpp"

class ComClass : public ICom {
    private:
        void onReceived(ComMessage * req);
};

extern ComClass COM;
#endif
