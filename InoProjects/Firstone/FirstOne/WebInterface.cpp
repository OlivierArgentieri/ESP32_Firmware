#include "WebInterface.h"
#include <WebServer.h>
#include <ESPAsyncWebServer.h>
#include "WMEEPROM.h"
#include "WMLog.h"
#include "WMNetwork.h"
#include <vector>

/**
* Public Methods
*/

void WebInterface::Setup()
{ 
  // Scan once
  WMNetwork::GetInstance().Scan();

  // Serve
  server = new AsyncWebServer(80);
  {
    server->on("/", HTTP_GET, [&](AsyncWebServerRequest *request) 
    {
      String content;
      CreateWebUI(content);      
      request->send(200, "text/html", content);
    });

    server->on("/rescan", HTTP_GET, [&](AsyncWebServerRequest *request) 
    {
      WMNetwork::GetInstance().Scan(true);
      request->redirect("/");
    });

    server->on("/connect", HTTP_POST, [&](AsyncWebServerRequest *request) 
    {
      WMNetworkData network_data;
      network_data.password = request->getParam(0)->value();
      network_data.ssid = request->getParam(1)->value();

      // Save data
      WMEEPROM::Save<WMNetworkData>(network_data, 0);
      request->send(200, "text/html", "Password saved, please reboot...");
    });
  }
  server->begin(); 
}

void WebInterface::Handler()
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
  std::vector<WMNetworkData> availableNetworks;
  WMNetwork::GetInstance().GetAvailableNetworks(availableNetworks);

  // Display available networks
  for (const WMNetworkData& network: availableNetworks )
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

