#include "WebInterface.h"
#include <WebServer.h>
#include <Wifi.h>
WebInterface* WebInterface::instance = nullptr;

/**
* Public Methods
*/

WebInterface* WebInterface::GetInstance()
{
  if(!instance)
  {
    instance = new WebInterface();
    return instance;
  }
}


void WebInterface::StartListening(HardwareSerial& Serial)
{
  String content;
  CreateWebUI(content);

  Serial.print("AAAA");
  static WebServer server(80);
  server.handleClient();
  {
    server.on("/", [&]() 
    {
      IPAddress ip = WiFi.softAPIP();
      Serial.print("Local IP: ");
      Serial.println(WiFi.localIP());
      Serial.print("SoftAP IP: ");
      Serial.println(WiFi.softAPIP());
      server.send(200, "text/html", content);
    });
  }

  server.begin();  
}

/**
* Private Methods
*/

void WebInterface::CreateWebUI(String& outContent)
{
  outContent = "<!DOCTYPE HTML>\r\n<html>Welcome to Wifi Credentials Update page";
  outContent += "<p>";
  outContent += "Test test test";
  outContent += "</p>";
  outContent += "</html>";
}

void WebInterface::GetAvailableNetworks(std::vector<WMNetwork>& outNetworks)
{
  outNetworks.clear();

  int n = WiFi.scanNetworks();
  for (int i = 0; i < n; ++i) {
    WMNetwork net;
    net.ssid = WiFi.SSID(i);
    net.rssi = WiFi.RSSI(i);
    net.open = WiFi.encryptionType(i) == WIFI_AUTH_OPEN;

    outNetworks.push_back(net);
  }
}


