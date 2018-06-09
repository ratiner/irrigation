#ifndef WEBREQUEST_H
#define WEBREQUEST_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "API/APISettings.hpp"
#include "com.hpp"
#include "debug.hpp"
#include "external.hpp"


class WebRequest {
    String url;
    String method;
    int version;
    String queryString;
    public:
        void setUrl(String&);
        void setMethod(String&);
        void setVersion(int&);
        void setQuerString(String&);
        bool handleRequest(WiFiClient&);
    private:
        void _doApiRequest(WiFiClient&);
        void _doStaticContent(WiFiClient&);
        char * _getContentType();
        void _doError(WiFiClient&, int, const char *);
      
};



#endif
