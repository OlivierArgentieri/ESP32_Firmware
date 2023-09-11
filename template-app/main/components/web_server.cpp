#include "web_interface.h"


/*
 * Private methods
 */ 

void web_interface::CreateWebUI(char* outContent)
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
  //std::vector<WMNetworkData> availableNetworks;
  //WMNetwork::GetInstance().GetAvailableNetworks(availableNetworks);

  // Display available networks
//   for (const WMNetworkData& network: availableNetworks )
//   {
//     outContent += "<tr>";

//     outContent += "<td>";
//     outContent += network.ssid; 
//     outContent += "</td>";
    
//     outContent += "<td>";
//     outContent += network.rssi;
//     outContent += "</td>";

//     outContent += "<td>";
//     outContent += network.open ? "Yes" : "No";
//     outContent += "</td>";
    
//     outContent += "<td>";
//     outContent += "<form action='/connect' method='post'>";
    
//     if (!network.open) outContent += "<input type='text' name='password' placeholder='password'>";
//     outContent += "<input type='text' name='ssid' value='" + network.ssid + "'>";
//     outContent += "<input type='submit' value='Connect'>";
//     outContent += "</form>";

//     outContent += "</td>";
//     outContent += "</tr>";
//   }

  outContent += "</table>";

  outContent += "</html>";
}
