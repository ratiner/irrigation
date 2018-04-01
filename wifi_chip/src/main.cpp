#include "main.hpp"

WebManager _webManager;
String header;

void setup()
{
  Com::begin();
  Debug::begin();
  
  Net network;
  network.create_access_point();
  _webManager.start();
  pinMode(16, OUTPUT);
  pinMode(5, OUTPUT);

 
}


void loop()
{
  _webManager.tryHandleClient();

      
    

    //Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
    //
}
