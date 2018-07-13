#ifndef SCHEDULER_SCTRUCTURES_H
#define SCHEDULER_SCTRUCTURES_H

#include <TimeStamp.hpp>

struct Counter {
    byte ports[2];
};

struct Valve {
    byte id;
    byte ports[2];
    byte mode;
};

/*
struct IOSettings {
    Counter main_counter;
    int valves_count;
    Valve * valves;
};*/


struct Program {
    const char * name;
    TimeStamp startTime;
    TimeStamp endTime;
    byte weekDays;
    int amount;
    Valve * valves;
    byte totalVales;
};

#endif
