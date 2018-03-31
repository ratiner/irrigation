#include "net.hpp"

Net::Net()
{
}

bool Net::create_access_point(void)
{
  IPAddress subnet(255, 255, 255, 0);
  _localIp.fromString(AP_IP);

  //boolean confOK = WiFi.softAPConfig(_localIp, _localIp, subnet);
  //Serial.println(confOK ? "AP Config OK!" : "AP Config Failed");

  boolean isConnected = WiFi.softAP(AP_NETWORK, AP_PASSWORD);
  Debug::println(isConnected ? "AP OK!" : "AP Failed! Password Short");

  if (isConnected)
  {
    _localIp = WiFi.softAPIP();
    Debug::print("Local IP: ");
    Debug::println(AP_IP);
  }
}

bool Net::connect(void)
{
}
