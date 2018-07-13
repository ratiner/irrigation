#include "main.hpp"

 int n;
void setup() {

    COM.begin();
    Wire.begin();
 

n=0;

    pinMode(13,OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(2, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(2), waterPulse, FALLING);
    digitalWrite(13,LOW);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    //started = 0;

    initIO();
    Scheduler.init();
}

void initIO () {
    ComMessage * io = COM.send(ComClass::CMD_READ, ComClass::KEY_IO, NULL);
    delete io;
}




void loop() {

    COM.listen();

    LinkedList<Program*> * progs = Scheduler.getPrograms();
    
    Serial.print("\nProgs ");
    Serial.println(progs->size());

    Program * p;
    for(int i=0; i< progs->size(); i++) 
    {
        p = progs->get(i);
        Serial.println(p->name);
    }
    delay(5000);
/*

     TimeStamp * t = CLOCK.getTime();

    if(started == 0 && t->compareTo(startTime) <=0) {
        //turn on led
      //  digitalWrite(13,HIGH);
        digitalWrite(8, HIGH);
        digitalWrite(9, LOW);
        delay(10);
        digitalWrite(8, HIGH);
        digitalWrite(9, HIGH);
        started = 1;
    }

   

   

    if(started == 1 && t->compareTo(endTime) <= 0) {
        //turn off led
        //digitalWrite(13,LOW);
        digitalWrite(8, LOW);
        digitalWrite(9, HIGH);
        delay(10);
        digitalWrite(8, HIGH);
        digitalWrite(9, HIGH);
        started =2 ;
    }
    //TODO: Kiril Stuff :)
    */
}

void waterPulse() {
    n++;
 
 //digitalWrite(13,HIGH);
}