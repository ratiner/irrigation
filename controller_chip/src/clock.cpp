#include "clock.hpp"
void Clock::begin()
{
  //DateTime now = RTC.now();
 // Serial.print(now.unixtime());
 // Serial.print("s = ");
 // Serial.print(now.unixtime() / 86400L);
  //Serial.println("d");
}

TimeStamp * Clock::getTime()
{
  if(_now == NULL)
    _now = new TimeStamp();

  //DateTime now = RTC.now();
    bool century = false;
    bool h12 = false;
    bool ampm = false;

  _now->year = DSClock.getYear();
  _now->month = DSClock.getMonth(century);
  _now->day = DSClock.getDate();
 // _now->doW = now.dayOfTheWeek();
  _now->hour = DSClock.getHour(h12, ampm);
  _now->min = DSClock.getMinute();
  _now->sec = DSClock.getSecond();

  return _now;
}

void Clock::setTime(TimeStamp &newTime)
{
  DSClock.setYear(newTime.year);
  DSClock.setMonth(newTime.month);
  DSClock.setDate(newTime.day);
 // DSClock.setDoW(newTime.doW);
  DSClock.setHour(newTime.hour);
  DSClock.setMinute(newTime.min);
  DSClock.setSecond(newTime.sec);
}