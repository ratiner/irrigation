#include "debug.hpp"

void Debug::begin(void)
{
    Serial.begin(1150000);
}

void Debug::print (String & text) 
{
    Serial.print(text);
   
}

void Debug::println (String & text) 
{
    print(text + "\n");
}

void Debug::print (const char * text)
{
    String str(text);
    print(str);
}

void Debug::println (const char * text) 
{
    String str(text);
    println(str);
}
