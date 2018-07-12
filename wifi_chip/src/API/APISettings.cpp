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
        JsonObject &netInfo = networks.createNestedObject();
        netInfo["SSID"] = WiFi.SSID(i);
        netInfo["RSSI"] = WiFi.RSSI(i);
        netInfo["SECURED"] = (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? false : true;
    }
    root.printTo(client);
}

void APISettings::Network_GetConfig(WiFiClient &client)
{
    NetworkSettings ns = Settings.getNetworkSettings();

    StaticJsonBuffer<512> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();

    root["ap_ip"] = ns.ap_ip;
    root["ap_network"] = ns.ap_network;
    root["ap_password"] = ns.ap_password;
    root["wifi_network"] = ns.wifi_network;
    root["wifi_password"] = ns.wifi_password;
    root["wifi_enabled"] = ns.wifi_enabled;
    root["RSSI"] = WiFi.RSSI();
    root["ip"] = ns.wifi_enabled ? WiFi.localIP().toString() :WiFi.softAPIP().toString();
    root.printTo(client);
}

void APISettings::Network_SetConfig(WiFiClient& client, String& body)
{
    Settings.setNetworkSettings(body);

    StaticJsonBuffer<100> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["Status"] = "OK";
    root.printTo(client);
}



void APISettings::Network_GetClock(WiFiClient &client)
{
    ComMessage * result = COM.send(ComClass::CMD_READ, ComClass::KEY_CLOCK, NULL);

    StaticJsonBuffer<50> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["stamp"] = result->getValue();
    root.printTo(client);
    delete result;
}

void APISettings::Network_SetClock(WiFiClient& client, String& body)
{
    ComMessage * result = COM.send(ComClass::CMD_WRITE, ComClass::KEY_CLOCK, body.c_str());
    StaticJsonBuffer<50> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["status"] = result->getValue();
    root.printTo(client);
    delete result;
}


void APISettings::IO_Get(WiFiClient &client)
{
    File io = Settings.getIOSettings();
    while (io.available())
        client.write(io);
    io.close();
}

void APISettings::IO_Set(WiFiClient& client, String& body)
{
    Settings.setIOSettings(body);

    StaticJsonBuffer<100> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["Status"] = "OK";
    root.printTo(client);
}