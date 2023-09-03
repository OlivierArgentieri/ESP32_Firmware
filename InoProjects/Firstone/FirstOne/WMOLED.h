#include <WString.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

class Adafruit_SSD1306;

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

    void DisplayMessage(const String& message) const;
  private:
    /**
      * private property 
      */ 
    static WMOLED* instance;
    Adafruit_SSD1306* display;
};