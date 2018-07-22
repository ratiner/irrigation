#include "APIScheduler.hpp"

void APIScheduler::Programs_Get(WiFiClient &client)
{
    byte count = Settings.getPrograms();

    StaticJsonBuffer<100> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();

    root["programs"] = count;
    root.printTo(client);
}

void APIScheduler::Program_Get(String & id, WiFiClient &client)
{
    File prog = Settings.getProgram(id);

    while (prog.available())
        client.write(prog);
    prog.close();
}

void APIScheduler::Program_Set(String & id, WiFiClient &client, String& body)
{
    Settings.setProgram(id, body);
     StaticJsonBuffer<100> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["Status"] = "OK";
    root.printTo(client);
}