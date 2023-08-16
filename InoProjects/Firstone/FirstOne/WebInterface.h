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
     * Private 
     */

  private:
    /**
     * Private Methods
     */
    
    /** Construct web interface */
    void CreateWebUI(String& outContent);

    /** Get list of available networks */
    //void GetAvailableNetworks(std::vector<WMNetwork>& outNetworks);
    
    /** Create routes */
    void CreateRoutes();

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
