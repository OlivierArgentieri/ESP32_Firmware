#include "WMNetwork.h"
#include <vector>
#include <EEPROM.h>
#include <Wifi.h>
class String;
class HardwareSerial;
class AsyncWebServer;

class WebInterface
{

  enum HandlerAction : int
  {
    NONE = 0,
    LISTNETWORKS = 1,
    CONNECTREQUEST = 2,
  };
  public:
    /**
    * Public Methods
    */

    /** Get Instance */
    static WebInterface* GetInstance();

    /** Server Setup */
    void Setup(HardwareSerial& Serial);

    /** Handle Route Behaviour */
    void Handler(HardwareSerial& Serial);

  private:
    /**
    * Private Methods
    */
    
    /** Construct web interface */
    void CreateWebUI(String& outContent);

    /** Get list of available networks */
    //void GetAvailableNetworks(std::vector<WMNetwork>& outNetworks);
    
    /** Clear EEPROM */
    void ClearEEPROM();

    /** Save to EEPROM */
   void WriteToEEPROM(const String& value, int padding);
   
   void Scan(bool force);
  private:
    /**
    * private property 
    */
    static WebInterface* instance;
    static AsyncWebServer* server;
    HandlerAction currentStatuts = HandlerAction::NONE;
    std::vector<WMNetwork> networksScanned;
};

inline WebInterface* WebInterface::GetInstance()
{
  if(!instance)
  {
    instance = new WebInterface();
  }
  return instance;
}

inline void WebInterface::ClearEEPROM()
{
  for (int i = 0; i < 96; ++i) {
    EEPROM.write(i, 0);
  }
}

inline void WebInterface::WriteToEEPROM(const String& value, int padding)
{
  const int len = value.length();
  for (int i = 0; i < len; ++i)
    EEPROM.write(padding + i, value[i]);
}

inline void WebInterface::Scan(bool force = false)
{
  if (!force && this->networksScanned.size() > 0)
    return;
  this->networksScanned.empty();

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