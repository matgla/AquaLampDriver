#include "hal/memory/eeprom.hpp"

#include <stm32f10x_flash.h>

constexpr u16 FLASH_PAGE_SIZE         = 0x400;
constexpr u32 LAST_BANK_START_ADDRESS = 0x08007c00;
constexpr u32 LAST_BANK_END_ADDRESS   = 0x080013ff;


namespace hal
{
namespace memory
{

Eeprom::Eeprom()
{
    FLASH_Unlock();
}

void Eeprom::write(std::size_t address, const gsl::span<const u8>& data)
{
}

const gsl::span<const u8>& Eeprom::read() const
{
}

} // namespace memory
} // namespace hal
