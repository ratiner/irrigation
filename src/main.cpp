#include "main.hpp"

WebManager _webManager;
String header;

void setup()
{
  Debug::begin();
  Serial.begin(9600);
  Serial.swap();
  
  Net network;
  network.create_access_point();
  _webManager.start();
  pinMode(16, OUTPUT);
  pinMode(5, OUTPUT);
}


void loop()
{
  _webManager.tryHandleClient();


   
    digitalWrite(16, HIGH);
     delay(500);
      digitalWrite(16, LOW);
      delay(500);

    //Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
    //delay(3000);
}
