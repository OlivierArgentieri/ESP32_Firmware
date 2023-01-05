#include "WMNetwork.h"
#include <vector>
#include <EEPROM.h>

class String;
class HardwareSerial;
class AsyncWebServer;

class WebInterface
{
  public:
    /**
    * Public Methods
    */

    /** Get Instance */
    static WebInterface* GetInstance();

    /** Server Setup */
    void Setup(HardwareSerial& Serial);
  private:
    /**
    * Private Methods
    */
    
    /** Construct web interface */
    void CreateWebUI(String& outContent);

    /** Get list of available networks */
    void GetAvailableNetworks(std::vector<WMNetwork>& outNetworks);
    
    /** Clear EEPROM */
    void ClearEEPROM();

    /** Save to EEPROM */
   void WriteToEEPROM(const String& value, int padding);
  private:
    /**
    * private property 
    */
    static WebInterface* instance;
    static AsyncWebServer* server;
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
