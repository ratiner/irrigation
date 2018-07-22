#include "main.hpp"

 int n;

 int counterFactor;

void setup() {
    COM.begin();
    Wire.begin();
 
    n=0;
    pinMode(13,OUTPUT);
    digitalWrite(13,LOW);
  
    initIO();
    Scheduler.init();
}

void initIO () {
    ComMessage * io = COM.send(ComClass::CMD_READ, ComClass::KEY_IO, NULL);

    StaticJsonBuffer<512> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(io->getValue());

    counterFactor = root["counter"]["factor"];
    JsonArray &counterPorts = root["counter"]["ports"];

    if(counterPorts.size() == 1)
    {
        int port = counterPorts.get<int>(0);
        pinMode(port, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(port), waterPulse, FALLING);
    }


    JsonArray &valves = root["valves"];
    for(int i =0; i< valves.size(); i++)
    {
        JsonObject & v = valves.get<JsonObject>(i);
        //id
        JsonArray & v_ports = v["ports"];
        for(int j=0; j<v_ports.size(); j++) 
        {
            pinMode(v_ports.get<int>(j), OUTPUT);
        }
    }
    
    stopValve(1);
}




void loop() {

    COM.listen();
    TimeStamp * t = CLOCK.getTime();

    LinkedList<Program*> * progs = Scheduler.getPrograms();

    Program * p;

    for(int i=0; i< progs->size(); i++) 
    {
        p = progs->get(i);
        
        if(!p->active) 
        {
            if(t->compareTo(p->startTime) == 0 && p->weekDays & (1 << t->doW-1))
            {
                p->active = 1;
                p->amountLeft = p->amount;
                String progId = "" + i;
               // ComMessage * res = COM.send(ComClass::CMD_WRITE, ComClass::KEY_START_PROG, "0");
               // delete res;
                
                startValve(1);
            }
        }
        else
        {
            if(t->compareTo(p->endTime) <=0 || p->amountLeft <= 0)
            {
                p->active = false;
                String progId = "" + i;
                //ComMessage * res = COM.send(ComClass::CMD_WRITE, ComClass::KEY_STOP_PROG, "0");
               // delete res;
                stopValve(1);
            }
            else 
            {
              //  String amount = "" + p->amountLeft;
               // ComMessage * res = COM.send(ComClass::CMD_SET_AMOUNT, i, amount.c_str());
               // delete res;
            }
        }
    }
}

void startValve(int id)
{
    //turn on led
    digitalWrite(13,HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    delay(100);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);

}
void stopValve(int)
{
    //turn off led
    digitalWrite(13,LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    delay(100);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
}

void waterPulse() {
    n++;

    LinkedList<Program*> * progs = Scheduler.getPrograms();
    Serial.println("interrupt");
    Program * p;
    for(int i=0; i< progs->size(); i++) 
    {
        p = progs->get(i);
        if(p->active)
        {
           p->amountLeft -= counterFactor;
        }
            
    }
}