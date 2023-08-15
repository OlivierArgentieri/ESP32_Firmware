#include <WString.h>

class HardwareSerial;

class WMLog
{
public:
	enum LogLevel : int
	{
		INFO = 0,
		DEBUG = 1,
		WARNING = 2,
		ERROR = 3,
	};

public:
  /**
   * Contructor
   */
  
  /** Default constructor */
  WMLog(const HardwareSerial& Serial);

public:
	/**
   * Public Methods
   */

	/** Log */
	void Log(const String& message, LogLevel level = LogLevel::INFO);

private:
  /**
   * private property 
   */
  inline static HardwareSerial* serial = nullptr;

  /** Dictionnary matching enum value and color value */
  static const String logLevelColors[];
   
};

const String WMLog::logLevelColors[] = 
{
    "\033[32m", // INFO
    "\033[34m", // DEBUG
    "\033[33m", // WARNING
    "\033[31m", // ERROR
};

inline WMLog::WMLog(const HardwareSerial& Serial)
{
	// store instance
	serial = const_cast<HardwareSerial*>(&Serial);
}

inline void WMLog::Log(const String& message, LogLevel level)
{
	// Print level
	serial->print(WMLog::logLevelColors[level]);

	// Print message
	serial->println(message);
}
