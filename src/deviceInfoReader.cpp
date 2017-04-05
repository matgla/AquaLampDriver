#include <stm32f4xx_dbgmcu.h>

#include "deviceInfoReader.hpp"

namespace deviceInfoReader
{
u16 readDeviceSignature()
{
    return (*reinterpret_cast<u16*>(DEVICE_ID_ADDRESS)) & 0x0fff;
}

u16 readDeviceRevision()
{
    return *(reinterpret_cast<u16*>(DBGMCU->IDCODE + 2));
}

u16 readFlashSize()
{
    return *reinterpret_cast<u16*>(FLASH_SIZE_ADDRESS);
}

void readUniqueId(u8* buffer)
{
    for (int i = 0; i < 12; ++i)
    {
        buffer[i] = *reinterpret_cast<u8*>(DEVICE_UNIQUE_ID_ADDRESS + i);
    }
}
}