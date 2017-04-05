#pragma once

#include "logger.hpp"
#include "messages.hpp"

class Handshake
{
  public:
    Handshake(Logger& logger);
    void perform();
    void registerClient(const ClientInfo& clientInfo);

  private:
    void waitForClient();
    void sendDeviceIdData();
    void send();
    bool connectedToClient_;
    Logger& logger_;
};