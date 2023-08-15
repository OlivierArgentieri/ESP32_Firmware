/*  This sketch demonstrates how to scan WiFi networks.
 *  The API is almost the same as with the WiFi Shield library,
 *  the most obvious difference being the different file you need to include:
 */
#include "WiFi.h"
#include "WebInterface.h"
#include "Log.h"

void setup()
{
  Serial.begin(115200);
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  WiFi.softAP("AAAAAAAA", "");
  WMNetwork other_network_data;
  WebInterface::GetInstance()->Setup(Serial);
  Serial.println("Setup done");
  //WebInterface::GetInstance()->GetNetworkData(other_network_data);
  
  // Serial.print("OK GET DATA FROM BOOT \n");
  // Serial.println(other_network_data.password);
  // Serial.println(other_network_data.ssid);
}
 
void loop()
{
  WebInterface::GetInstance()->Handler(Serial);
}