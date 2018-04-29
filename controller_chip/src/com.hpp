#ifndef COM_H
#define COM_H

#include <Arduino.h>
#include <icom.hpp>

class Com : public ICom {
    private:
        void onReceived(ComMessage * req);
};
#endif
