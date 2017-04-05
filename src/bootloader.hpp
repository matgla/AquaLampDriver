#pragma once

#include "handshake.hpp"
#include "logger.hpp"

class BootLoader
{
  public:
    BootLoader(Logger& logger);
    ~BootLoader();
    bool specialMode();
    void bootSpecialMode();
    void bootFW();
    void handleEvent(void* event, u8 size);

  private:
    void bootRecovery();
    void bootDFU();

    Logger& logger_;
    Handshake handshake_;
};