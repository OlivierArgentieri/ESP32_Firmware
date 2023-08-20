#include "WiFi.h"
#include "WebInterface.h"
#include "WMNetwork.h"
#include "WMEEPROM.h"
#include "WMLog.h"

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA); /*ESP32 Access point configured*/


  delay(100);
  WiFi.softAP("AAAAAAAA", "");
  WebInterface::GetInstance().Setup(Serial);
  LOG_DEBUG("setup done!");
  Serial.println(WiFi.softAPIP()); 
  IPAddress ip = WiFi.softAPIP();
  LOG_DEBUG(String(WiFi.softAPIP()));

  WMNetworkData network_data;
  WMEEPROM::Get<WMNetworkData>(network_data, 0);
  LOG_DEBUG("OK GET Network DATA");
  LOG_INFO(network_data.password);
  LOG_INFO(network_data.ssid);

  bool validConnection = WMNetwork::GetInstance().isValidConnection(network_data);
  if (validConnection)
  {
    LOG_INFO("Connected to " + network_data.ssid);
    Serial.println(WiFi.localIP());
  }
}

void loop()
{
  WebInterface::GetInstance().Handler(Serial);
}
