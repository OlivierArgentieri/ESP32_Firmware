#pragma once
#include "interfaces/component.h"

struct WebServer: public IComponent{

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

  private:
    /**
     * private methods
     */
    void CreateWebUI(char* outContent);
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
