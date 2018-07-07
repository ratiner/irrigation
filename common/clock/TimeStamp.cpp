#include "TimeStamp.hpp"

int TimeStamp::compareTo(TimeStamp &otherTime)
{
    //1 high
    //0 equals
    //-1 lower
/*
    if (otherTime.year > year)
        return 1;
    else if (otherTime.year < year)
        return -1;
    else
    {
        if (otherTime.month > month)
            return 1;
        else if (otherTime.month < month)
            return -1;
        else
        {
            if (otherTime.day > day)
                return 1;
            else if (otherTime.day < day)
                return -1;
            else
            {
                */
                if (otherTime.hour > hour)
                    return 1;
                else if (otherTime.hour < hour)
                    return -1;
                else
                {
                    if (otherTime.min > min)
                        return 1;
                    else if (otherTime.min < min)
                        return -1;
                    else
                    {
                        if (otherTime.sec > sec)
                            return 1;
                        else if (otherTime.sec < sec)
                            return -1;
                        else
                        {
                            return 0;
                        }
                    }
                }
           /* }
        }
    } */
}

const char * TimeStamp::getStr() 
{
    //YYYY-MM-DDTHH:mm:ssZ
    char str[20];
    snprintf(str, 21, "%04d-%02d-%02dT%02d:%02d:%02dZ", 2000+year, month, day, hour, min, sec);
    return str;
}