#include "WebInterface.h"
#include <WebServer.h>
#include <Wifi.h>
#include <ESPAsyncWebServer.h>

WebInterface* WebInterface::instance = nullptr;
AsyncWebServer* WebInterface::server = nullptr;

/**
* Public Methods
*/

void WebInterface::Setup(HardwareSerial& Serial)
{ 
  // create cspecific class for that
  
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
      Serial.print("PARAM: ");
    
      Serial.println("CLEAR");
      ClearEEPROM();
      Serial.println("OK CLEAR");

      auto a = request->params();
      Serial.println(a);
    
      //WriteToEEPROM(String(a), 0);
      // const String pass = request->getParam(0)->value();
      // Serial.println(pass);
      // WriteToEEPROM(pass, 0);
      // Serial.print("OK WRITE PASS");
      // const String ssid = request->getParam(1)->value();
      // Serial.println(ssid);
      // WriteToEEPROM(ssid, 32);
      // Serial.print("OK WRITE SSID");

      // String read;
      // ReadFromEEPROM(read, 32);
      // Serial.print("OK READ SSID\n");
      // Serial.print(read);
      
      // ReadFromEEPROM(read, 0);
      // Serial.print("OK READ PASSWORD \n");
      // Serial.print(read);
      WMNetwork network_data;
      network_data.password = request->getParam(0)->value();
      network_data.ssid = request->getParam(1)->value();
      
      Serial.println(network_data.password);
      Serial.println(network_data.ssid);


      SaveNetworkData(network_data);
      Serial.print("OK WRITE DATA\n");


      WMNetwork other_network_data;
      GetNetworkData(other_network_data);

      Serial.print("OK GET DATA\n");
      Serial.println(network_data.password);
      Serial.println(network_data.ssid);
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


