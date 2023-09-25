#ifndef WEB_SERVER_H_
#define WEB_SERVER_H_

#include "esp_http_server.h"
  
static const char* html_content = "<html><body><h1>Hello, ESP32!</h1></body></html>";
static esp_err_t root_handler(httpd_req_t *req) {
    httpd_resp_send(req, html_content, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

static const httpd_uri_t root_uri = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = root_handler,
    .user_ctx  = NULL
};

void init_http_server(void){
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  httpd_handle_t server = NULL;
  if (httpd_start(&server, &config) == ESP_OK) {
    httpd_register_uri_handler(server, &root_uri);
  }
}


#endif // WEB_SERVER_H_

