#include <WString.h>
#include "Component.h"

struct WMNetwork
{
  String ssid;
  String rssi;
  String password;
  bool open;
};


class WMNetworkComponent : protected WMComponent
{
public:
  /**
   * Contructor
   */
  
  /** Default constructor */
  WMNetworkComponent();
  
public:
  /**
   * Public Methods
   */

  /** Override Init method */
  void init();

  /** Override Clean method */
  void clean();
};

inline WMNetworkComponent::WMNetworkComponent()
{
  // Do nothing
}

inline void WMNetworkComponent::init()
{
  // Do nothing
}

inline void WMNetworkComponent::clean()
{
  // Do nothing
}