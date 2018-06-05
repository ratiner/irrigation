#include "main.hpp"

String header;
WebManager _webManager;
Com com;

void setup()
{
  Debug::begin();
  Net network;



  network.create_access_point();
  //network.connect();
  _webManager.start();
  com.begin();
}


void loop()
{
  _webManager.tryHandleClient();
  com.listen();
}
