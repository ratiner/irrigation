#include "main.hpp"

String cmd;
External * external;

void setup() {
    // put your setup code here, to run once:
    //_com = new Com();
    //_com->begin();
    
    Debug::begin();
    Debug::println("hello");
    external = new External();
    external->init();

    pinMode(4, OUTPUT);
    pinMode(3, INPUT);
    digitalWrite(4, HIGH);

Serial.begin(9600);
     Wire.begin(4);        // join i2c bus (address optional for master)
     Wire.onRequest(requestEvent);
     Wire.onReceive(receiveEvent);
}

void requestEvent() {
  Wire.write("hello "); // respond with message of 6 bytes
  Serial.println("req event");
  // as expected by master
}

void receiveEvent(int iData) {
    Serial.println("recieve event");
    Serial.println(iData);
    while(Wire.available())
        Serial.write(Wire.read());
}



void loop() {
  //  _com->listen();

/*
if(digitalRead(3) == HIGH)
{

 File fl = external->getFile("/vendor/bootstrap.min.css");

    if(fl)
    {
         while (fl.available())
            Serial.write(fl.read());
            
        fl.close();
    }

}
*/
delay(1000);
    
}