#include <Arduino.h>

class Com {
    const String  _start = ":::";
    const String _split = ",,,";
    const String _end = ";;;";
    
    String _buffer;
    public:
        void begin (void);
        void listen(void);
        void set (int cmd, int key, int value);
        void set (int cmd, int key, const char * value);
        void get (int cmd, int key);
       
};