#include "main.hpp"

TimeStamp startTime;
TimeStamp endTime;

Clock clk;
void setup() {
    Wire.begin();
 Serial.begin(9600);
    startTime.year = 2018;
    startTime.month = 6;
    startTime.day = 9;
    startTime.hour = 20;
    startTime.min = 40;
    startTime.sec = 0;

     clk.setTime(startTime);

     startTime.sec = 10;

    endTime.year = 2018;
    endTime.month = 6;
    endTime.day = 9;
    endTime.hour = 20;
    endTime.min = 40;
    endTime.sec = 15;
    

    _com = new Com();
    _com->begin();
    clk.begin();
    pinMode(13,OUTPUT);

   
   
}





void loop() {
    _com->listen();
     TimeStamp * t = clk.getTime();
   
   Serial.print(t->compareTo(startTime));
    if(t->compareTo(startTime) <=0) {
        //turn on led
        digitalWrite(13,HIGH);
    }

   

   

    if(t->compareTo(endTime) <= 0) {
        //turn off led
        digitalWrite(13,LOW);
    }
    //TODO: Kiril Stuff :)
}