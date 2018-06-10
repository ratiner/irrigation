#include "net.hpp"

Net::Net()
{
}

bool Net::create_access_point(void)
{
}

bool Net::connect(void)
{
  int status = WL_IDLE_STATUS;
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Debug::println("WiFi shield not present");
    while (true);
  }

  NetworkSettings ns = Settings.getNetworkSettings();
  if (ns.wifi_enabled)
  {
    status = WiFi.begin(ns.wifi_network, ns.wifi_password);
    while (status != WL_CONNECTED)
    {
      Debug::print(".");
      delay(500);
    }

    Debug::print("Connected, IP address: ");
    Debug::println(WiFi.localIP().toString().c_str());
  }
  else
  {
    IPAddress subnet(255, 255, 255, 0);
    _localIp.fromString(ns.ap_ip);
    WiFi.softAPConfig(_localIp, _localIp, subnet);

    boolean isConnected = WiFi.softAP(ns.ap_network, ns.ap_password);
    Debug::println(isConnected ? "AP OK!" : "AP Failed! Password Short");

    if (isConnected)
    {
      _localIp = WiFi.softAPIP();
      Debug::print("Local IP: ");
      Debug::println(ns.ap_ip);
    }
  }
}
