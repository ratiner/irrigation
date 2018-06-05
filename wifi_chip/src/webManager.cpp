#include "webManager.hpp"



WebManager::WebManager(External * external)
{
  _external = external;
}

bool WebManager::start(void)
{
 
  _com = new Com();
  _com->begin();

  _server = new WiFiServer(80);
  _server->begin();
  
  Debug::println("WebServer is listening on port: 80");
}

bool WebManager::tryHandleClient(void) 
{
  WiFiClient c = _server->available();   // Listen for incoming clients
 // c.setNoDelay(1);

  if (!c || !c.connected())
    return false; //if no client
  _client = &c;

  Debug::println("New Client.");          // print a message out in the serial port
  this->getRequest();
  String method = _req.substring(0, _req.indexOf(" "));
  String path = _req.substring(_req.indexOf(" ")+2, _req.indexOf("HTTP/1."));
  path.trim();
  if(path.length() == 0 || path.charAt(0) !='/')
    path = '/' + path;

  Debug::print("Method: ");
  Debug::println(method);
  Debug::print("Path: ");
  Debug::println(path);
  
  if(path.indexOf("/api/") > -1) 
  {
     //handle api request
     if(path.indexOf("1/on") > 0) {







int n = WiFi.scanNetworks();
  Debug::println("scan done");
  if (n == 0) {
    Debug::println("no networks found");
  } else {
    Serial1.print(n);
    Debug::println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial1.print(i + 1);
      Debug::print(": ");
      Serial1.print(WiFi.SSID(i));
      Serial1.print(" (");
      Serial1.print(WiFi.RSSI(i));
      Debug::print(")");
      Serial1.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");















       //_com->send(1, 1, "1");
     }
     if(path.indexOf("1/off") > 0) {
       _com->send(1, 1, "0");
     }
  }
  else 
  {
    //static content - sd-card
    this->doStaticContent(path);
  }
  
  _client->println(); // The HTTP response ends with another blank line

  _req = "";
  // Close the connection
  
  _client->stop();
  Debug::println("Client disconnected.");
  Debug::println("");
  
}


void WebManager::getRequest() 
{
  this->_req = "";
  String currentLine = "";              // make a String to hold incoming data from the client
  while (_client->connected())            // loop while the client's connected
  {            
    if (_client->available())             // if there's bytes to read from the client,
    {             
      char c = _client->read();           // read a byte, then
      //Debug::write(c);                // print it out the serial monitor
      this->_req += c;
      if (c == '\n')                    // if the byte is a newline character
      {                    
        if (currentLine.length() > 0) 
          currentLine = "";             // if you got a newline, then clear currentLine
        else                              
          break;                        // exit white. reached end
      } 
      else if (c != '\r')               // if you got anything else but a carriage return character,
        currentLine += c;               // add it to the end of the currentLine
    }
  } 
}

void WebManager::doStaticContent(String path) 
{
  String fileName = path.substring(path.lastIndexOf('/')+1, path.length());
  if(fileName.indexOf('.') == -1)
  {
    if(path.charAt(path.length()-1) != '/')
      path += "/";
    path += "index.htm";
  }

  char * contentType = this->getContentType(path);

  Debug::print("Resolving: ");
  Debug::print(path);
  Debug::print(" - ");
  Debug::println(contentType);


  if(!_external->exists(path.c_str()))
  {
      path = "/index.htm"; //fix for angular rewrite module.
      if(!_external->exists(path.c_str()))
      {
        this->doError(404, "File not found");
        Debug::println("File not found");
        return;
      }
  }

  File fl = _external->getFile(path.c_str());

  if(fl)
  {
    _client->println("HTTP/1.1 200 OK");
    _client->print("Content-type:");
    _client->println(contentType);
    _client->print("Cache-Control:");
    _client->println("max-age=321274");
    _client->println("Connection: close");
    _client->println();

    
    while (fl.available())
      _client->write(fl);
    fl.close();
  }
  else  {
    this->doError(500, "File read error");
    Debug::println("File read error");
  }
  
}

void WebManager::doError(int errorCode, const char * message)
{
  switch(errorCode)
  {
    case 404:
      _client->println("HTTP/1.1 404 NotFound");
      break;
  }
  _client->println("Content-type:text/html");
  _client->println("Connection: close");
  _client->println();

  _client->print("Error: ");
  _client->println(message);
}

char * WebManager::getContentType(String path) 
{
  int end =  path.indexOf("?");
  if(end < 0)
    end = path.length();

  String ext = path.substring(path.indexOf("."), end);
  ext.trim();
  Debug::print("Ext: ");
  Debug::println(ext);

  if(ext == ".html" || ext == ".htm")
    return "text/html";
  else if(ext == ".jpg" || ext == ".jpeg")
    return "image/jpeg";
  else if(ext == ".png")
    return "image/png";
  else if(ext == ".gif")
    return "image/gif";
  else if(ext == ".css")
    return "text/css";
  else if(ext == ".js")
    return "application/javascript";
  else if(ext == ".xml")
    return "application/xml";
  else
    return "text/plain";
}
