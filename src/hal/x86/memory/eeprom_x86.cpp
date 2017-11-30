#include "hal/memory/eeprom.hpp"

#include <cstring>

#include "hal/utils/assert.hpp"
#include "utils.hpp"

namespace hal
{
namespace memory
{

u8 flash[1024];

Eeprom::Eeprom()
    : currentAddress_(0),
      logger_("EEPROM")
{
}
void Eeprom::write(std::size_t address, const gsl::span<const uint32_t>& data)
{
    HAL_ASSERT_MSG(address + data.size() < sizeof(flash), "Flash exceeded");
    std::memcpy(flash + address, data.data(), data.size());
}

const gsl::span<const uint32_t> Eeprom::read(const uint32_t address, const uint32_t size) const
{
    HAL_ASSERT_MSG(address + size < sizeof(flash), "Flash exceeded");
    return gsl::span<const uint32_t>{reinterpret_cast<uint32_t*>(flash) + address, static_cast<int>(size)};
}

} // namespace memory
} // namespace hal
