
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
  
  private:
    /**
    * private property 
    */
    static WebInterface* instance;
};
