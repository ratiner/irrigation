#ifndef COM_H
#define COM_H

#include <Arduino.h>
#include <icom.hpp>
#include "clock.hpp"
#include <TimeStamp.hpp>
#include "scheduler.hpp"
#include <SchedulerStructures.hpp>
#include <LinkedList.hpp>

class ComClass : public ICom {
    private:
        void onReceived(ComMessage * req);
};

extern ComClass COM;
#endif
