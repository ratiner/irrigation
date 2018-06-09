#include "settings.hpp"

struct NetworkSettings SettingsClass::getNetworkSettings()
{
    File file = SD.open(networkSettingsFile);

    if(!file)
        Debug::println("Failed to open");


    StaticJsonBuffer<512> jsonBuffer;

    JsonObject &root = jsonBuffer.parseObject(file);
    file.close();
    if (!root.success())
        Debug::println("Failed to read file, using default configuration");
    
    NetworkSettings ns;
    ns.ap_ip = root["ap_ip"] | "172.16.0.1";
    ns.ap_network = root["ap_network"] | "Irrigation Controller";
    ns.ap_password = root["ap_password"] | "";
    ns.wifi_network = root["wifi_network"] | "";
    ns.wifi_password = root["wifi_password"] | "";
    ns.wifi_enabled = root["wifi_enabled"] | false;
    return ns;
}


SettingsClass Settings;