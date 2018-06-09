#include "external.hpp"

ExternalClass::ExternalClass()
{
}

bool ExternalClass::init(void)
{
    if(_isInit)
        return true;
    
    Debug::print("Initializing SD card...");

    if (!SD.begin(SS)) {
        Debug::println("initialization failed!");
        return false;
    }

    Debug::println("initialization done.");
    this->_isInit = true;
}

File ExternalClass::getFile(const char * path) {
    //if(!this->init())
    //    return false;
    
    File f = SD.open(path, FILE_READ);
    if(!f)
        Debug::println("Failed to open");
    return f;
}

bool ExternalClass::exists(const char * path) {
    return SD.exists(path);
}

ExternalClass External;