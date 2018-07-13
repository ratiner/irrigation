#include "main.hpp"

String header;
WebServer *_webServer;

void setup()
{
  Debug::begin();
  External.init();

  Net network;

  network.connect();

  _webServer = new WebServer();
  _webServer->begin();
  COM.begin();

  Debug::println("Ver:1.04");
}

void loop()
{
  _webServer->handleClient();
  COM.listen();
}
