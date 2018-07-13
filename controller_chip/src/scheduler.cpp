#include "scheduler.hpp"

void SchedulerClass::init()
{
    programs = LinkedList<Program*>();

    ComMessage *progs = COM.send(ComClass::CMD_READ, ComClass::KEY_PROGRAM, NULL);
    byte total = progs->getValue().toInt();
    delete progs;
 

    Program * p;
    for (int i = 0; i < total; i++)
    {
        String idx = String(i);
        ComMessage *prog = COM.send(ComClass::CMD_READ, ComClass::KEY_PROGRAM, idx.c_str());
        
        StaticJsonBuffer<512> jsonBuffer;
        JsonObject &root = jsonBuffer.parseObject(prog->getValue());
        if (root.success())
        {
            p = new Program();
            p->name = root["name"]; 
            //p.startTime = startTime
            //p.endTime = endTime
            p->weekDays = 0x00000101;
            p->amount = 50;
            //p.valves =
            programs.add(p);
        }

        delete prog;
    }
}

LinkedList<Program *> * SchedulerClass::getPrograms() 
{
    return &this->programs;
}

SchedulerClass Scheduler;