#include "com.hpp"
const char* const Com::_start = ":::";
const char* const Com::_split = ",,,";
const char* const Com::_end = ";;;";


void Com::begin(void)
{
    Serial.begin(9600);
}

void Com::set (int cmd, int key, const char * value)
{
    Serial.print(Com::_start);
    Serial.print(cmd);
    Serial.print(Com::_split);
    Serial.print(key);
    Serial.print(Com::_split);
    Serial.print(value);
    Serial.print(Com::_end);
}

void Com::get (int cmd, int key) 
{

}