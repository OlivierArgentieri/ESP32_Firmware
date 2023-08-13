/*  This sketch demonstrates how to scan WiFi networks.
 *  The API is almost the same as with the WiFi Shield library,
 *  the most obvious difference being the different file you need to include:
 */
#include "WiFi.h"
#include "WebInterface.h"
void setup()
{
  Serial.begin(115200);
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  WiFi.softAP("AAAAA", "");
  
  WebInterface::GetInstance()->Setup(Serial);
  Serial.println("Setup done");
}
 
void loop()
{
  WebInterface::GetInstance()->Handler(Serial);
}