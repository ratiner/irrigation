#include "webRequest.hpp"


bool WebRequest::handleRequest(WiFiClient& client)
{
    if (url.indexOf("/api/") > -1)
        _doApiRequest(client);
    else
        _doStaticContent(client);  //static content - sd-card
       
    client.println(); // The HTTP response ends with another blank line
    client.flush();
    return true;
}


void WebRequest::_doApiRequest(WiFiClient& client)
{  
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:application/json");
        client.println("Connection:close");
        client.println();

        if(url.indexOf("/api/settings/network/scan") > -1)
        {
            APISettings::Network_ScanWiFi(client);
        }

        else if(url.indexOf("/api/settings/network") > -1) 
        {
            if(method == "POST")
                APISettings::Network_SetConfig(client, body);
            else
                APISettings::Network_GetConfig(client);
        }
        else if(url.indexOf("/api/settings/clock") > -1) 
        {
            if(method == "POST")
                APISettings::Network_SetClock(client, body);
            else
                APISettings::Network_GetClock(client);

        }
        else if(url.indexOf("/api/settings/io") > -1) 
        {
            if(method == "POST")
                APISettings::IO_Set(client, body);
            else 
                APISettings::IO_Get(client);
        }

        else if(url.indexOf("/api/scheduler") > -1) 
        {
            String id = url.substring(15);
            if(id.length() == 0)
                APIScheduler::Programs_Get(client);
            //else if(method == "POST") 
                //APIScheduler::Program_Set(client, body);
            else
                APIScheduler::Program_Get(id, client);
        }

      
        else if (url.indexOf("1/on") > 0)
        {
            COM.send(ComClass::CMD_MANUAL, ComClass::KEY_OPEN, "1");
        }

        else if (url.indexOf("1/off") > 0)
        {
            COM.send(ComClass::CMD_MANUAL, ComClass::KEY_CLOSE, "1");
        }

        else if (url.indexOf("status") > 0) 
        {
            ComMessage * msg = COM.send(ComClass::CMD_READ, ComClass::KEY_STATUS, NULL);
            
            
            StaticJsonBuffer<100> jsonBuffer;
            JsonObject &root = jsonBuffer.createObject();

            root["active"] =  msg->getValue();
            root.printTo(client);            
        }

        else 
            _doError(client, 404, "Method API was in found");

}

void WebRequest::_doStaticContent(WiFiClient& client)
{
    String &path = this->url;
    String fileName = path.substring(path.lastIndexOf('/') + 1, path.length());
    if (fileName.indexOf('.') == -1)
    {
        if (path.charAt(path.length() - 1) != '/')
            path += "/";
        path += "index.htm";
    }

    char *contentType = _getContentType();

    Debug::print("Resolving: ");
    Debug::print(path);
    Debug::print(" - ");
    Debug::println(contentType);

    if (!External.exists(path.c_str()))
    {
        path = "/index.htm"; //fix for angular rewrite module.
        if (!External.exists(path.c_str()))
        {
            _doError(client, 404, "File not found");
            Debug::println("File not found");
            return;
        }
    }

    File fl = External.getFile(path.c_str());

    if (fl)
    {
        Debug::print("Sending");
        client.println("HTTP/1.1 200 OK");
        client.print("Content-type:");
        client.println(contentType);
        client.print("Cache-Control:");
        client.println("max-age=321274");
        client.println("Connection:close");
        client.println();
        while (fl.available())
            client.write(fl);
        fl.close();

        Debug::println("Done.");
    }
    else
    {
        _doError(client, 500, "File read error");
        Debug::println("File read error");
    }
}

void WebRequest::_doError(WiFiClient& client, int errorCode, const char *message)
{
    switch (errorCode)
    {
    case 404:
        client.println("HTTP/1.1 404 NotFound");
        break;
    }
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();

    client.print("Error: ");
    client.println(message);
}


char *WebRequest::_getContentType()
{
    String& path = this->url;
    int end = path.indexOf("?");
    if (end < 0)
        end = path.length();

    String ext = path.substring(path.indexOf("."), end);
    ext.trim();
    Debug::print("Ext: ");
    Debug::println(ext);

    if (ext == ".html" || ext == ".htm")
        return "text/html";
    else if (ext == ".jpg" || ext == ".jpeg")
        return "image/jpeg";
    else if (ext == ".png")
        return "image/png";
    else if (ext == ".gif")
        return "image/gif";
    else if (ext == ".css")
        return "text/css";
    else if (ext ==".ico")
        return "image/x-icon";
    else if (ext == ".js")
        return "application/javascript";
    else if (ext == ".xml")
        return "application/xml";
    else
        return "text/plain";
}


void WebRequest::setUrl(String &strUrl)
{
    this->url = strUrl;
}
void WebRequest::setMethod(String &strMethod)
{
    this->method= strMethod;
}
void WebRequest::setVersion(int &iVersion)
{
    this->version = iVersion;
}
void WebRequest::setQuerString(String &query)
{
    this->queryString = query;
}
void WebRequest::setBody(String &body)
{
    this->body = body;
}