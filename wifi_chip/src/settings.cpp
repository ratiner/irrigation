#include "settings.hpp"

struct NetworkSettings SettingsClass::getNetworkSettings()
{
    File file = SD.open(networkSettingsFile, FILE_READ);
    if (!file)
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

void SettingsClass::setNetworkSettings(String &settings)
{
    File file = SD.open(networkSettingsFile, O_WRITE | O_CREAT | O_TRUNC);
    if (!file)
        Debug::println("Failed to open");
    file.print(settings);
    file.close();
}

File &SettingsClass::getIOSettings()
{
    File file = SD.open(ioSettingsFile, FILE_READ);
    if (!file)
    {
        Debug::println("Failed to open");
    }
    return file;
}

void SettingsClass::setIOSettings(String &settings)
{
    File file = SD.open(ioSettingsFile, O_WRITE | O_CREAT | O_TRUNC);
    if (!file)
        Debug::println("Failed to open");
    file.print(settings);
    file.close();
}

byte SettingsClass::getPrograms()
{
    byte c = 0;
    File dir = SD.open(programSettingsFolder);
    if (!dir)
        Debug::println("Failed to open");
    else
    {
        while (true)
        {
            File entry = dir.openNextFile();
            if (!entry)
            {
                // no more files
                break;
            }
            if (!entry.isDirectory())
                c++;
            entry.close();
        }
    }
    dir.close();
    return c;
}

File &SettingsClass::getProgram(String &index)
{
    return this->getProgram(index, FILE_READ);
}

File &SettingsClass::getProgram(String &index, uint8_t mode)
{
    String path = programSettingsFolder;
    path += index + ".cfg";
    File entry= SD.open(path, mode);
    if (!entry)
        Debug::println("Failed to open");
    return entry;


}

void SettingsClass::setProgram(String &index, String &program)
{

    File file = this->getProgram(index, O_WRITE | O_CREAT | O_TRUNC);
    if (!file)
        Debug::println("Failed to open");
    file.print(program);
    file.close();
}

SettingsClass Settings;