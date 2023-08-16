#include <EEPROM.h>

class WMEEPROM {
  public:
    /**
     * Static Public Methods
     */

    /** Save object to EEPROM */
    template<typename T>
    static void Save(const T& object, int address)
    {
      // Write object to EEPROM
      EEPROM.put(address, object);
      EEPROM.commit();
    }

    /** Get object from EEPROM */
    template<typename T>
    static void Get(T& object, int address)
    {
      // Read object from EEPROM
      EEPROM.get(address, object);
    }

    /** Clear EEPROM */
    static void Clear()
    {
      for (int i = 0; i < 512; ++i) {
        EEPROM.write(i, 0);
      }
      EEPROM.commit();
    }
};
