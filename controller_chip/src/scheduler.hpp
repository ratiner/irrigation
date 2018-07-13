#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SchedulerStructures.hpp>
#include <LinkedList.hpp>
#include "com.hpp"

class SchedulerClass {
    byte total;
    LinkedList<Program*> programs;
    public:
        void init();
        LinkedList<Program *> * getPrograms();
};

extern SchedulerClass Scheduler;
#endif
