#include "main.hpp"

String header;
WebManager * _webManager;
Com com;
External * _external;

void setup()
{
  Debug::begin();
  _external = new External();
  _external->init();

  Net network;
  
  network.connect();

  _webManager = new WebManager(_external);
  _webManager->start();
  com.begin();
}


void loop()
{
  _webManager->tryHandleClient();
  com.listen();
}
