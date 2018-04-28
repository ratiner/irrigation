#include "external.hpp"

External::External()
{
}

bool External::init(void)
{
    if(_isInit)
        return true;
    
    _SD = new SdFat();

    Debug::print("Initializing SD card...");

    if (!_SD->begin(SS)) {
        Debug::println("initialization failed!");
        return false;
    }

    Debug::println("initialization done.");
    this->_isInit = true;
}

File External::getFile(const char * path) {
   // if(!this->init())
      //  return NULL;
    
    File f = _SD->open(path, FILE_READ);
    if(!f)
        Debug::println("Failed to open");
    return f;
}

bool External::exists(const char * path) {
   return _SD->exists(path);
}