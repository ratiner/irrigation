#include "scheduler.hpp"

void SchedulerClass::init()
{
    int i, j;
    ComMessage * result;
    StaticJsonBuffer<512> jsonBuffer;

    programs = LinkedList<Program*>();

    result = COM.send(ComClass::CMD_READ, ComClass::KEY_PROGRAM, NULL);
    byte total = result->getValue().toInt();

    Program * p;
    for (i = 0; i < total; i++)
    {
        String idx = String(i);
        result = COM.send(ComClass::CMD_READ, ComClass::KEY_PROGRAM, idx.c_str());
        
        JsonObject &root = jsonBuffer.parseObject(result->getValue());
        String * name;
        String dt;

        if (root.success())
        {
            name = new String();
            *name = (const char *)root["name"]; 
            p = new Program();
            p->active = root["active"];
            p->name =name->c_str();
            dt = "0000-00-00T";
            dt += (const char *)root["startTime"];
            p->startTime.fromStr(dt.c_str());

            dt = "0000-00-00T";
            dt += (const char *)root["endTime"];
            p->endTime.fromStr(dt.c_str());

            JsonArray &days = root["weekDays"];

            p->weekDays = 0;
            for(j=0; j<= days.size(); j++) {
                p->weekDays |= 1 << days.get<int>(j);
            }
            
            p->amount = 10;//root["amount"];
            p->amountLeft =0;
            //p.valves =
            programs.add(p);
        }

    }

  Serial.print("Loaded: ");
  Serial.println(programs.size());
}

LinkedList<Program *> * SchedulerClass::getPrograms() 
{
    return &this->programs;
}

SchedulerClass Scheduler;