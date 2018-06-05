#include "net.hpp"

Net::Net()
{
}

bool Net::create_access_point(void)
{
  
}

bool Net::connect(void)
{
  Settings * settings = new Settings();
  NetworkSettings ns =  settings->getNetworkSettings();
  if(ns.wifi_enabled)
  {
    _localIp = WiFi.begin(ns.wifi_network.c_str(), ns.wifi_password.c_str());
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Debug::print(".");
    }
    Debug::print("Connected, IP address: ");
    Debug::println(WiFi.localIP().toString().c_str());
  }
  else 
  {
      IPAddress subnet(255, 255, 255, 0);
      _localIp.fromString(ns.ap_ip);
      WiFi.softAPConfig(_localIp, _localIp, subnet);

      boolean isConnected = WiFi.softAP(ns.ap_network.c_str(), ns.ap_password.c_str());
      Debug::println(isConnected ? "AP OK!" : "AP Failed! Password Short");

      if (isConnected)
      {
        _localIp = WiFi.softAPIP();
        Debug::print("Local IP: ");
        Debug::println(ns.ap_ip);
      }
  }

  delete settings;
}
