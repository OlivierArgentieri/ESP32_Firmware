class String;
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
    void Setup();

    /** Handle Route Behaviour */
    void Handler();

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
    static inline WebInterface* instance = nullptr;
    static inline AsyncWebServer* server = nullptr;
    HandlerAction currentStatuts = HandlerAction::NONE;
};
