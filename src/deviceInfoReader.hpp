#pragma once

#include "types.h"

#define DEVICE_ID_ADDRESS 0xe0042000
#define DEVICE_UNIQUE_ID_ADDRESS 0xfff7a10
#define FLASH_SIZE_ADDRESS 0x1fff7a22

namespace deviceInfoReader
{
u16 readDeviceSignature();
u16 readDeviceRevision();
u16 readFlashSize();
void readUniqueId(u8* buffer);
}