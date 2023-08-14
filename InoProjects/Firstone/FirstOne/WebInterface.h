#include "WMNetwork.h"
#include <vector>
#include <EEPROM.h>
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
   
    /** Save to EEPROM */
    void ReadFromEEPROM(String& out, int padding);

    /** Save to static scan network method */
    void Scan(bool force = false);

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
  for (int i = 0; i < 512; ++i) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
}

inline void WebInterface::WriteToEEPROM(const String& value, int padding)
{
  const int len = value.length();
  for (int i = 0; i < len; ++i)
    EEPROM.write(padding + i, value[i]);
  EEPROM.commit();
}

inline void WebInterface::ReadFromEEPROM(String& out, int padding)
{
  out = "";
  int newStrLen = EEPROM.read(padding);
  char data[newStrLen + 1];
  for (int i = 0; i < newStrLen; ++i) {
    int result = EEPROM.read(padding+i);
    if (result == 255)
      break;
    data[i] = result;
  }
    
  data[newStrLen] = '\0';
  out = String(data);
}
