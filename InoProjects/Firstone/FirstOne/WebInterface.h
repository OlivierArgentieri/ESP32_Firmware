#include "WMNetwork.h"
#include <vector>

class String;
class HardwareSerial;
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
};
