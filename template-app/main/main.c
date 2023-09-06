#include <stdio.h>
#include <string.h>
#include "esp_wifi.h"

#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"


static const char *TAG = "wifi softAP";
void init_log(void)
{
  /*
   * There are 5 log levels:
   * ESP_LOGE (error)
   * ESP_LOGW (warning)
   * ESP_LOGI (info)
   * ESP_LOGD (debug)
   * ESP_LOGV (verbose)
   */
  ESP_LOGI(TAG, "ESP_WIFI_MODE_AP");
}

void init_nvs(void)
{
  /* nvs is a non-volatile storage
   * it is used to store data that should be persistent
   * even after a reboot
   * here, it will be used to store wifi credentials
   */ 

  esp_err_t err = nvs_flash_init();
  if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {    
    // assert like
    ESP_ERROR_CHECK(nvs_flash_erase());
    err = nvs_flash_init();
  }
}


void app_main(void)
{
  init_log();
  init_nvs();
}
