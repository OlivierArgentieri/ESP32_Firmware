#pragma once

#include "component.h"

class WebServer : public IComponent {

public:
  /**
   * public virtual methods
   */ 
    WebServer();
    ~WebServer();

    void start();
    void stop();

  public:
    /**
     * public virtual methods
     */
    void init() override;
};


/**
 * Inline methods
*/

inline WebServer::WebServer() {
  // empty
}

inline WebServer::~WebServer() {
  // empty
}

inline void WebServer::start() {
  // empty
}

inline void WebServer::stop() {
  // empty
}

inline void WebServer::init() {
  // empty
}
