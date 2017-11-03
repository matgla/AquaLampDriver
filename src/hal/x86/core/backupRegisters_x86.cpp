#include "hal/core/backupRegisters.hpp"

#define STARTUP_REGISTER 1
#define STARTUP_MAGIC_COOKIE 0xBEEF

namespace hal
{
namespace core
{

BackupRegisters& BackupRegisters::get()
{
    static BackupRegisters br;
    return br;
}

bool BackupRegisters::isFirstStartup()
{
    // TODO: implement
    return true;
}

void BackupRegisters::write(u16 registerNumber, u16 value)
{
    // TODO: implement
}

void BackupRegisters::startupDone()
{
    if (isFirstStartup())
    {
        write(STARTUP_REGISTER, STARTUP_MAGIC_COOKIE);
    }
}

BackupRegisters::BackupRegisters()
{
    // TODO: implement
}


} // namespace hal
} // namespace core