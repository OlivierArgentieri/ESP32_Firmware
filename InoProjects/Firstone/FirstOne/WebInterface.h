#include "WMNetwork.h"
#include <vector>

class String;
class HardwareSerial;
class WebServer;
class WebInterface
{
  public:
    /**
    * Public Methods
    */

    /** Get Instance */
    static WebInterface* GetInstance();

    /** Server Listen */
    void StartListening(HardwareSerial& Serial);

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
    
  private:
    /**
    * private property 
    */
    static WebInterface* instance;
    static WebServer* server;
};

inline WebInterface* WebInterface::GetInstance()
{
  if(!instance)
  {
    instance = new WebInterface();
  }
  return instance;
}

