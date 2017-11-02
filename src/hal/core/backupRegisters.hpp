#pragma once

#include "logger/logger.hpp"
#include "utils/types.hpp"

namespace hal
{
namespace core
{

class BackupRegisters
{
  public:
    static BackupRegisters& get();
    bool isFirstStartup();
    void startupDone();

  private:
    void write(u16 registerNumber, u16 value);
    BackupRegisters();
};

} // namespace hal
} // namespace core