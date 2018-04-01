#include "debug.hpp"

void Debug::begin(void)
{
    Serial1.begin(9600);
}

void Debug::print (String & text) 
{
    Serial1.print(text);
   
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
