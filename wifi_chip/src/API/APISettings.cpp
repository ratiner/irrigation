#include "APISettings.hpp"

void APISettings::Network_ScanWiFi(WiFiClient &client)
{
    int n = WiFi.scanNetworks(); //get number of networks

    StaticJsonBuffer<1000> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["total"] = n;

    JsonArray &networks = root.createNestedArray("networks");

    for (int i = 0; i < n; ++i)
    {
        JsonObject& netInfo = networks.createNestedObject();
        netInfo["SSID"] = WiFi.SSID(i);
        netInfo["RSSI"] = WiFi.RSSI(i);
        netInfo["SECURED"] = (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? false: true;
    }
    root.printTo(client);
    jsonBuffer.clear();
}