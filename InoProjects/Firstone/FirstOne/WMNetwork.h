#include <WString.h>
#include "Component.h"

#pragma pack(1)
struct WMNetworkData
{
  String ssid;
  String rssi;
  String password;
  bool open;
};
#pragma pack(pop)

class WMNetwork : WMComponent
{
public:
  /**
   * Contructor
   */
  
  /** Default constructor */
  WMNetwork();
  
public:
  /**
   * Public Methods
   */

  /** GetInstance */
  static WMNetwork& GetInstance() {
    static WMNetwork instance(Serial);
    return instance;
  }

  /** Scan network method */
  void Scan(bool force = false);

  private:
    /**
     * Private Property 
     */
    inline static std::vector<WMNetwork> networksScanned;
};

/** inline */
void WMNetworkComponent::Scan(bool force)
{
  if (!force && this->networksScanned.size() > 0)
    return;

  networksScanned.clear();

  int n = WiFi.scanNetworks();
  for (int i = 0; i < n; ++i)
  {
    WMNetworkData network;
    network.ssid = WiFi.SSID(i);
    network.rssi = WiFi.RSSI(i);
    network.open = WiFi.encryptionType(i) == WIFI_AUTH_OPEN;
    networksScanned.push_back(network);
  }
}
