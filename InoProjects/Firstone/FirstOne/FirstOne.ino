/*  This sketch demonstrates how to scan WiFi networks.
 *  The API is almost the same as with the WiFi Shield library,
 *  the most obvious difference being the different file you need to include:
 */
#include "WiFi.h"
#include "WebInterface.h"
#include "WMNetwork.h"
#include "WMLog.h"
#include "WMEEPROM.h"

void setup()
{
  Serial.begin(115200);
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  WiFi.softAP("AAAAAAAA", "");
  WebInterface::GetInstance().Setup(Serial);
  LOG_DEBUG("setup done!");

  WMNetworkData network_data;
  WMEEPROM::Get<WMNetworkData>(network_data, 0);
  LOG_DEBUG("OK GET Network DATA");
  LOG_INFO(network_data.password);
  LOG_INFO(network_data.ssid);
}
 
void loop()
{
  WebInterface::GetInstance().Handler(Serial);
}