#include "hal/memory/eeprom.hpp"

#include <cstring>

#include <stm32f10x_flash.h>

#include "hal/utils/assert.hpp"

constexpr u16 FLASH_PAGE_SIZE         = 0x400;
constexpr u32 LAST_BANK_START_ADDRESS = 0x08000000 + FLASH_PAGE_SIZE * 63; // PAGE31
constexpr u32 LAST_BANK_END_ADDRESS   = 0x08000000 + FLASH_PAGE_SIZE * 63;


namespace hal
{
namespace memory
{

Eeprom::Eeprom()
    : currentAddress_(0),
      logger_("EEPROM")
{
}

void erase()
{
    FLASH_Unlock();
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
    FLASH_ErasePage(LAST_BANK_START_ADDRESS);
    FLASH_Lock();
}

void burnFlash(uint32_t startAddress, const gsl::span<const u32>& data)
{
    FLASH_Unlock();
    const uint32_t* bufferPtr = reinterpret_cast<const uint32_t*>(data.data());
    uint32_t currentAddress   = startAddress;
    while (currentAddress < startAddress + data.size())
    {
        FLASH_ProgramWord(currentAddress, *bufferPtr);
        currentAddress += 4;
        ++bufferPtr;
    }
    FLASH_Lock();
}

bool checkCorrectness(uint32_t startAddress, const gsl::span<const uint32_t>& data)
{
    const uint32_t* bufferPtr = reinterpret_cast<const uint32_t*>(data.data());
    uint32_t currentAddress   = startAddress;

    while (currentAddress < startAddress + data.size())
    {
        if (*bufferPtr != *(reinterpret_cast<uint32_t*>(currentAddress)))
        {

            return false;
        }
        currentAddress += 4;
        ++bufferPtr;
    }
    return true;
}

void Eeprom::write(std::size_t address, const gsl::span<const uint32_t>& data)
{
    HAL_ASSERT_MSG(address + data.size() < FLASH_PAGE_SIZE, "Trying to write after flash end");

    uint32_t buffer[FLASH_PAGE_SIZE / sizeof(uint32_t)];

    std::memcpy(buffer, reinterpret_cast<uint32_t*>(LAST_BANK_START_ADDRESS), FLASH_PAGE_SIZE);
    std::memcpy(buffer + address, data.data(), data.size());

    if (checkCorrectness(LAST_BANK_START_ADDRESS, gsl::span<const uint32_t>{buffer, FLASH_PAGE_SIZE - sizeof(uint32_t)}))
    {
        logger_.info() << "No data changes";
        return;
    }

    erase();


    burnFlash(LAST_BANK_START_ADDRESS, gsl::span<const uint32_t>{buffer, FLASH_PAGE_SIZE - sizeof(uint32_t)});
    currentAddress_ = 0;

    if (!checkCorrectness(LAST_BANK_START_ADDRESS, gsl::span<const uint32_t>{buffer, FLASH_PAGE_SIZE - sizeof(uint32_t)}))
    {
        logger_.error() << "Write to flash failed";
        return;
    }
    logger_.info() << "Write successful!";
}

const gsl::span<const uint32_t> Eeprom::read(const uint32_t address, const uint32_t size) const
{
    HAL_ASSERT_MSG(address + size < FLASH_PAGE_SIZE, "Trying to read after flash end");

    return gsl::span<const uint32_t>{reinterpret_cast<uint32_t*>(LAST_BANK_START_ADDRESS) + address, static_cast<const int>(size)};
}

} // namespace memory
} // namespace hal
