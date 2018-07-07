#include "main.hpp"

TimeStamp startTime;
TimeStamp endTime;
 int n;
 int started;
Clock clk;
void setup() {
    Wire.begin();
 Serial.begin(9600);
 
    startTime.year = 18;
    startTime.month = 6;
    startTime.day = 9;
    startTime.hour = 20;
    startTime.min = 40;
    startTime.sec = 0;

     clk.setTime(startTime);

     startTime.sec = 10;

    endTime.year = 18;
    endTime.month = 6;
    endTime.day = 9;
    endTime.hour = 20;
    endTime.min = 40;
    endTime.sec = 15;
    

n=0;
    //_com = new Com();
    //_com->begin();
    clk.begin();
    pinMode(13,OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(2, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(2), waterPulse, FALLING);
    digitalWrite(13,LOW);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    started = 0;
}





void loop() {

   // _com->listen();
     TimeStamp * t = clk.getTime();
   Serial.println(t->compareTo(startTime));
    if(started == 0 && t->compareTo(startTime) <=0) {
        //turn on led
        digitalWrite(13,HIGH);
        digitalWrite(8, HIGH);
        digitalWrite(9, LOW);
        delay(10);
        digitalWrite(8, HIGH);
        digitalWrite(9, HIGH);
        started = 1;
    }

   

   

    if(started == 1 && t->compareTo(endTime) <= 0) {
        //turn off led
        digitalWrite(13,LOW);
        digitalWrite(8, LOW);
        digitalWrite(9, HIGH);
        delay(10);
        digitalWrite(8, HIGH);
        digitalWrite(9, HIGH);
        started =2 ;
    }
    //TODO: Kiril Stuff :)
}

void waterPulse() {
    n++;
 
 //digitalWrite(13,HIGH);
}