#include "clock.hpp"
void Clock::begin()
{
  DateTime now = RTC.now();
 // Serial.print(now.unixtime());
 // Serial.print("s = ");
 // Serial.print(now.unixtime() / 86400L);
  //Serial.println("d");
}

TimeStamp * Clock::getTime()
{
  if(_now == NULL)
    _now = new TimeStamp();

  DateTime now = RTC.now();
  _now->year = now.year();
  _now->month = now.month();
  _now->day = now.day();
 // _now->doW = now.dayOfTheWeek();
  _now->hour = now.hour();
  _now->min = now.minute();
  _now->sec = now.second();


  Serial.print("Get: ");
   Serial.print(_now->year);
   Serial.print("-");
   Serial.print(_now->month);
   Serial.print("-");  
   Serial.print(_now->day);
   Serial.print("  "); 
   Serial.print(_now->hour);
   Serial.print(":");
   Serial.print(_now->min);
   Serial.print(":");  
   Serial.print(_now->sec);
   Serial.println();

  return _now;
}

void Clock::setTime(TimeStamp &newTime)
{
   Serial.print("Set: ");
   Serial.print(newTime.year);
   Serial.print("-");
   Serial.print(newTime.month);
   Serial.print("-");  
   Serial.print(newTime.day);
   Serial.print("  "); 
   Serial.print(newTime.hour);
   Serial.print(":");
   Serial.print(newTime.min);
   Serial.print(":");  
   Serial.print(newTime.sec);
   Serial.println(); 

  DSClock.setYear(newTime.year);
  DSClock.setMonth(newTime.month);
  DSClock.setDate(newTime.day);
 // DSClock.setDoW(newTime.doW);
  DSClock.setHour(newTime.hour);
  DSClock.setMinute(newTime.min);
  DSClock.setSecond(newTime.sec);
}