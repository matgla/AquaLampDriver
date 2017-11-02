#include "hal/core/backupRegisters.hpp"

#include <stm32f10x.h>

#define STARTUP_REGISTER BKP_DR1
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
    return BKP_ReadBackupRegister(STARTUP_REGISTER) != STARTUP_MAGIC_COOKIE;
}

void BackupRegisters::write(u16 registerNumber, u16 value)
{
    PWR_BackupAccessCmd(ENABLE);
    BKP_WriteBackupRegister(registerNumber, value);
    PWR_BackupAccessCmd(DISABLE);
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
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    if (isFirstStartup())
    {
        BKP_DeInit();
    }
}


} // namespace hal
} // namespace core