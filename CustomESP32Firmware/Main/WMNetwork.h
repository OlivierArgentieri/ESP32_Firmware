#ifndef WM_NETWORK_H
#define WM_NETWORK_H

#include <WString.h>
#include <vector>
#include <Wifi.h>
#include "WMLog.h"
#define DELAY(ms) for (unsigned long i = 0; i < ms; i++) { __asm("nop"); }

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
  String ssid;
  String password;
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

  WMNetworkData(
    const String local_ip,
    const String mask,
    const String gateway,
    const String first_dns,
    const String second_dns,
    const String ssid,
    const String password,
    const String rssi,
    bool open
    )
  {
    this->localIP.fromString(local_ip);
    this->mask.fromString(mask);
    this->gateway.fromString(gateway);
    this->firstDNS.fromString(first_dns);
    this->secondaryDNS.fromString(second_dns);
    this->ssid = ssid;
    this->password = password;
    this->rssi = rssi;
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
    if (!WiFi.config(network.localIP, network.gateway, network.mask))
    {
      LOG_ERROR("Failed to configure static IP");
      return false;
    }
  }
  
  // TODO set hostname in struct
  WiFi.setHostname("COUCOU");

  WiFi.begin(network.ssid, network.password);

  int timeout = 10;
  while (WiFi.status() != WL_CONNECTED && timeout > 0)
  {
    timeout--;
    DELAY(1000);
  }

  return WiFi.status() == WL_CONNECTED;
}
#endif
