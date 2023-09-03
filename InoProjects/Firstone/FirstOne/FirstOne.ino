#include "WiFi.h"
#include "WebInterface.h"
#include "WMNetwork.h"
#include "WMEEPROM.h"
#include "WMLog.h"
#include "WMOLED.h"

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA); /*ESP32 Access point configured*/
  delay(100);
  WiFi.softAP("AAAAAAAA", "");
  WebInterface::GetInstance().Setup(Serial);
  LOG_DEBUG("setup done!");
  
  IPAddress ip = WiFi.softAPIP();
  LOG_DEBUG(WiFi.softAPIP().toString());

  WMNetworkData network_data;
  WMEEPROM::Get<WMNetworkData>(network_data, 0);
  LOG_DEBUG("OK GET Network DATA");
  LOG_INFO(network_data.password);
  LOG_INFO(network_data.ssid);

  WMOLED::GetInstance().Setup();

  bool validConnection = WMNetwork::GetInstance().isValidConnection(network_data);
  if (validConnection)
  {
    LOG_INFO("Connected to " + network_data.ssid);    
    LOG_INFO(WiFi.localIP().toString());
    WMOLED::GetInstance().DisplayMessage(WiFi.localIP().toString());
  }
  else
  {
    WMOLED::GetInstance().DisplayMessage("AP IP: " + WiFi.softAPIP().toString());
  }

}

void loop()
{
  WebInterface::GetInstance().Handler(Serial);
}
