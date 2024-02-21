#include <WString.h>
#include <vector>
#include <Wifi.h>
#include "WMLog.h"

struct WNIPAddress
{
  uint first;
  uint second;
  uint third;
  uint fourth;
};

struct WMNetworkData
{
  IPAddress localIP;
  IPAddress mask;
  IPAddress gateway;
  IPAddress firstDNS;
  IPAddress secondaryDNS;
  String password;
  String ssid;
  String rssi;
  bool open;

  WMNetworkData()
  {
    localIP = IPAddress(0, 0, 0, 0);
    mask = IPAddress(0, 0, 0, 0);
    gateway = IPAddress(0, 0, 0, 0);
    firstDNS = IPAddress(0, 0, 0, 0);
    secondaryDNS = IPAddress(0, 0, 0, 0);
    ssid = "";
    rssi = "";
    password = "";
    open = false;
  }

  WMNetworkData(const String local_ip, const String mask, const String gateway, const String first_dns, const String second_dns, const String ssid, const String rssi, const String password, bool open)
  {
    this->localIP.fromString(local_ip);
    this->mask.fromString(mask);
    this->gateway.fromString(gateway);
    this->firstDNS.fromString(first_dns);
    this->secondaryDNS.fromString(second_dns);
    this->ssid = ssid;
    this->rssi = rssi;
    this->password = password;
    this->open = open;
  }

  // is_static_configured
  bool isStaticConfigured() const
  {
    return localIP != IPAddress(0, 0, 0, 0) && mask != IPAddress(0, 0, 0, 0) && gateway != IPAddress(0, 0, 0, 0);
  }
  
};

class WMNetwork
{
public:
  /**
   * Public Methods
   */

  /** GetInstance */
  static WMNetwork& GetInstance() {
    static WMNetwork instance;
    return instance;
  }

  /** Scan network method */
  void Scan(bool force = false);

  /** Get list of available networks */
  void GetAvailableNetworks(std::vector<WMNetworkData>& outNetworks);

  /** isValidConnection ?*/
  bool isValidConnection(const WMNetworkData& network);

  private:
    /**
     * Private Property 
     */
    std::vector<WMNetworkData> networksScanned;
};

/** inline */
inline void WMNetwork::Scan(bool force)
{
  if (!force && networksScanned.size() > 0)
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

inline void WMNetwork::GetAvailableNetworks(std::vector<WMNetworkData>& outNetworks)
{
  outNetworks = networksScanned;
}

inline bool WMNetwork::isValidConnection(const WMNetworkData& network)
{
  if(network.isStaticConfigured())
  {
    LOG_INFO(network.password);
    LOG_INFO(network.ssid);
    LOG_INFO(network.localIP.toString());
    LOG_INFO(network.mask.toString());
    LOG_INFO(network.gateway.toString());
    if (!WiFi.config(network.localIP, network.gateway, network.mask))
    {
      LOG_ERROR("Failed to configure static IP");
      return false;
    }
  }
  WiFi.setHostname("COUCOU");

  WiFi.begin(network.ssid, network.password);

  int timeout = 10;
  while (WiFi.status() != WL_CONNECTED && timeout > 0)
  {
    timeout--;
    delay(1000);
  }

  return WiFi.status() == WL_CONNECTED;
}
