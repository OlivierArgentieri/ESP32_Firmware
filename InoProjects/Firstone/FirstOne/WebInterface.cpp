#include "WebInterface.h"
#include <WebServer.h>
#include <Wifi.h>
#include <ESPAsyncWebServer.h>
#include "wmeeprom.h"
#include "wmlog.h"

WebInterface* WebInterface::instance = nullptr;
AsyncWebServer* WebInterface::server = nullptr;

/**
* Public Methods
*/


void WebInterface::Setup(HardwareSerial& Serial)
{ 
  // create specific class for that
  EEPROM.begin(512);
  // Scan once
  Scan();

  // Serve
  server = new AsyncWebServer(80);
  {
    server->on("/", HTTP_GET, [&](AsyncWebServerRequest *request) 
    {
      String content;
      CreateWebUI(content);      
      IPAddress ip = WiFi.softAPIP();
      Serial.print("SoftAP IP: ");
      Serial.println(WiFi.softAPIP());
      request->send(200, "text/html", content);
    });

    server->on("/rescan", HTTP_GET, [&](AsyncWebServerRequest *request) 
    {
      Scan(true);
      request->redirect("/");
    });

    server->on("/connect", HTTP_POST, [&](AsyncWebServerRequest *request) 
    {
      IPAddress ip = WiFi.softAPIP();
      
      LOG_DEBUG("Trying to get data");

      WMNetwork network_data;
      network_data.password = request->getParam(0)->value();
      network_data.ssid = request->getParam(1)->value();
      

      LOG_DEBUG(network_data.password);
      LOG_DEBUG(network_data.ssid);
      WMEEPROM::Save<WMNetwork>(network_data, 0);

      request->send(200, "text/html", "OK");
    });
  }
  server->begin(); 
}

void WebInterface::Handler(HardwareSerial& Serial)
{
    if (currentStatuts == HandlerAction::NONE)
      return;  

    if (currentStatuts == HandlerAction::LISTNETWORKS)
    {
    String aa;
      CreateWebUI(aa);
      
    }
}
/**
* Private Methods
*/

void WebInterface::CreateWebUI(String& outContent)
{
  outContent = "<!DOCTYPE HTML>\r\n<html>Wifi Credentials Update page";
  outContent += "<div>";
  outContent += "<a href='/rescan'>";
  outContent += "<button>Refresh</button>";
  outContent += "</a>";
  outContent += "</div>";

  outContent += "<table>";
  outContent += "<tr>";
  outContent += "<th> SSID </th>";
  outContent += "<th> RSSI </th>";
  outContent += "<th> OPEN </th>";
  outContent += "<th> Action </th>";
  outContent += "</tr>";

  outContent += "</td>";
  
  
  // Get available networks
  //std::vector<WMNetwork> availableNetworks;
  //GetAvailableNetworks(availableNetworks);
  for (const WMNetwork& network: this->networksScanned)
  {
    outContent += "<tr>";

    outContent += "<td>";
    outContent += network.ssid; 
    outContent += "</td>";
    
    outContent += "<td>";
    outContent += network.rssi;
    outContent += "</td>";

    outContent += "<td>";
    outContent += network.open ? "Yes" : "No";
    outContent += "</td>";
    
    outContent += "<td>";
    outContent += "<form action='/connect' method='post'>";
    
    if (!network.open) outContent += "<input type='text' name='password' placeholder='password'>";
    outContent += "<input type='text' name='ssid' value='" + network.ssid + "'>";
    outContent += "<input type='submit' value='Connect'>";
    outContent += "</form>";

    outContent += "</td>";
    outContent += "</tr>";
  }

  outContent += "</table>";

  outContent += "</html>";
}

void WebInterface::Scan(bool force)
{
  if (!force && this->networksScanned.size() > 0)
    return;

  networksScanned.clear();

  int n = WiFi.scanNetworks();
  for (int i = 0; i < n; ++i)
  {
    WMNetwork network;
    network.ssid = WiFi.SSID(i);
    network.rssi = WiFi.RSSI(i);
    network.open = WiFi.encryptionType(i) == WIFI_AUTH_OPEN;
    networksScanned.push_back(network);
  }
}


