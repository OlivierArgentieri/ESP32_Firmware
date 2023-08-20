#include <WString.h>
#include <vector>
#include <Wifi.h>

struct WMNetworkData
{
  String ssid;
  String rssi;
  String password;
  bool open;
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
  WiFi.begin(network.ssid, network.password);
  int timeout = 10;
  while (WiFi.status() != WL_CONNECTED && timeout > 0)
  {
    timeout--;
    delay(1000);
  }

  return WiFi.status() == WL_CONNECTED;
}