#include "WiFi.h"
#include "WebInterface.h"
#include "WMNetwork.h"
#include "WMEEPROM.h"
#include "WMLog.h"
#include "WMOLED.h"

// Define custom macros to avoid using delay function
#define DELAY(ms) for (unsigned long i = 0; i < ms; i++) { __asm("nop"); }

int main(){
  setup();
  while(true){
    loop();
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  DELAY(1000);

  WiFi.softAP("AAAAAAAA", "");
  LOG_DEBUG("setup done!");

  IPAddress ip = WiFi.softAPIP();
  LOG_DEBUG(WiFi.softAPIP().toString());

  WMNetworkData network_data;

  WMEEPROM::Get<WMNetworkData>(network_data, 0);
  LOG_DEBUG("OK GET Network DATA");
  LOG_INFO(network_data.password);
  LOG_INFO(network_data.ssid);
  LOG_INFO(network_data.localIP.toString());
  LOG_INFO(network_data.mask.toString());
  LOG_INFO(network_data.gateway.toString());


  bool validConnection = WMNetwork::GetInstance().isValidConnection(network_data);

  if (validConnection)
  {
    LOG_INFO("Connected to " + network_data.ssid);    
    LOG_INFO(WiFi.localIP().toString());
    WMOLED::GetInstance().DisplayMessage(WiFi.localIP().toString());
    return;
  }
  WMOLED::GetInstance().DisplayMessage("AP IP: " + WiFi.softAPIP().toString()); 
  LOG_INFO("AP IP: " + WiFi.softAPIP().toString());

}

// void setup() {}
void loop() {
  WebInterface::GetInstance().Handler();
}

// void setup()
// {
//   Serial.begin(115200);
//   WiFi.mode(WIFI_AP_STA); /*ESP32 Access point configured*/
//   WiFi.softAP("AAAAAAAA", "");
//   WebInterface::GetInstance().Setup();
//   LOG_DEBUG("setup done!");
  
//   IPAddress ip = WiFi.softAPIP();
//   LOG_DEBUG(WiFi.softAPIP().toString());

//   WMNetworkData network_data;

//   WMEEPROM::Get<WMNetworkData>(network_data, 0);
//   LOG_DEBUG("OK GET Network DATA");
//   LOG_INFO(network_data.password);
//   LOG_INFO(network_data.ssid);
//   LOG_INFO(network_data.localIP.toString());
//   LOG_INFO(network_data.mask.toString());
//   LOG_INFO(network_data.gateway.toString());

//   //WMOLED::GetInstance().Setup();

//   bool validConnection = WMNetwork::GetInstance().isValidConnection(network_data);

//   if (validConnection)
//   {
//     LOG_INFO("Connected to " + network_data.ssid);    
//     LOG_INFO(WiFi.localIP().toString());
//     WMOLED::GetInstance().DisplayMessage(WiFi.localIP().toString());
//     return;
//   }
//   WMOLED::GetInstance().DisplayMessage("AP IP: " + WiFi.softAPIP().toString()); 
//   LOG_INFO("AP IP: " + WiFi.softAPIP().toString());
// }

// void loop()
// {
//   WebInterface::GetInstance().Handler();
// }
