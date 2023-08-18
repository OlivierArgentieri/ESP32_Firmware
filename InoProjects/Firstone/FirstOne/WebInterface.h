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
    // TODO define macro for that
    static WebInterface& GetInstance() {
      static WebInterface instance;
      return instance;
    }
    
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

    /** Create routes */
    void CreateRoutes();
  
  private:
    /**
     * Private Routes
     */

  private:
    /**
    * private property 
    */
    static WebInterface* instance;
    static AsyncWebServer* server;
    HandlerAction currentStatuts = HandlerAction::NONE;
};

