#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

class WMOLED
{
  public:
    /**
     * Public Methods
     */

    /** Get Instance */
    // TODO define macro for that
    static WMOLED& GetInstance() {
      static WMOLED instance;
      return instance;
    }

    /** Setup */
    void Setup();
  private:
    /**
      * private property 
      */ 
    static WMOLED* instance;
};