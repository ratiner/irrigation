#include "webServer.hpp"

WebServer::WebServer()
    : _server(80), _currentStatus(HC_NONE), _statusChange(0)
{
}

bool WebServer::begin(void)
{
    _server.begin();

    Debug::println("WebServer is listening on port: 80");
    return true;
}

void WebServer::handleClient(void)
{
    if (_currentStatus == HC_NONE)
    {
        WiFiClient client = _server.available();
        if (!client)
        {
            return;
        }

        _client = client;
        _currentStatus = HC_WAIT_READ;
        _statusChange = millis();
    }

    if (_client == NULL || !_client.connected())
    {
        _client = WiFiClient();
        _currentStatus = HC_NONE;
        return;
    }

    // Wait for data from client to become available
    if (_currentStatus == HC_WAIT_READ)
    {
        if (!_client.available())
        {
            if (millis() - _statusChange > HTTP_MAX_DATA_WAIT)
            {
                _close();
            }
            yield();
            return;
        }
        Debug::println("Client connected");

        if (!_parseRequest())
        {
            _close();
            return;
        }
        _client.setTimeout(HTTP_MAX_SEND_WAIT);

        bool handled = _req->handleRequest(_client);
        delete _req;

        if (handled || !_client.connected())
        {
            _close();
            return;
        }
        else
        {
            _currentStatus = HC_WAIT_CLOSE;
            _statusChange = millis();
            return;
        }
    }

    if (_currentStatus == HC_WAIT_CLOSE)
    {
        if (millis() - _statusChange > HTTP_MAX_CLOSE_WAIT)
        {
            _close();
        }
        else
        {
            yield();
            return;
        }
    }
}

bool WebServer::_close(void)
{
    //if(_client)
    //     _client.stop();

    _client = WiFiClient();
    _currentStatus = HC_NONE;

    Debug::println("Client disconnected.");
    Debug::println("");
}

bool WebServer::_parseRequest(void)
{
    // Read the first line of HTTP request
    String req = _client.readStringUntil('\r');
    _client.readStringUntil('\n');

    // First line of HTTP request looks like "GET /path HTTP/1.1"
    // Retrieve the "/path" part by finding the spaces
    int addr_start = req.indexOf(' ');
    int addr_end = req.indexOf(' ', addr_start + 1);
    if (addr_start == -1 || addr_end == -1)
    {
        return false;
    }

    String method = req.substring(0, addr_start);
    String url = req.substring(addr_start + 1, addr_end);
    String versionEnd = req.substring(addr_end + 8);
    int version = atoi(versionEnd.c_str());
    String searchStr = "";
    int hasSearch = url.indexOf('?');
    if (hasSearch != -1)
    {
        searchStr = urlDecode(url.substring(hasSearch + 1));
        url = url.substring(0, hasSearch);
    }

    String header;
    String body;
    if (method == "POST" || method == "PUT")
    {
        header = _client.readStringUntil('\r');
        _client.readStringUntil('\n');
        while(header != "") {
            header = _client.readStringUntil('\r');
            _client.readStringUntil('\n');
        }

        body = _client.readStringUntil('\r');
        _client.readStringUntil('\n');
        while(header != "") {
            body += _client.readStringUntil('\r');
            _client.readStringUntil('\n');
        }
    }

    _req = new WebRequest();
    _req->setMethod(method);
    _req->setVersion(version);
    _req->setQuerString(searchStr);
    _req->setUrl(url);
    _req->setBody(body);
    _client.flush();
    return true;
}

String WebServer::urlDecode(const String &text)
{
    String decoded = "";
    char temp[] = "0x00";
    unsigned int len = text.length();
    unsigned int i = 0;
    while (i < len)
    {
        char decodedChar;
        char encodedChar = text.charAt(i++);
        if ((encodedChar == '%') && (i + 1 < len))
        {
            temp[2] = text.charAt(i++);
            temp[3] = text.charAt(i++);

            decodedChar = strtol(temp, NULL, 16);
        }
        else
        {
            if (encodedChar == '+')
            {
                decodedChar = ' ';
            }
            else
            {
                decodedChar = encodedChar; // normal ascii char
            }
        }
        decoded += decodedChar;
    }
    return decoded;
}
