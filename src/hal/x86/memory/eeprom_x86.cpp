#include "hal/memory/eeprom.hpp"

#include "utils.hpp"

namespace hal
{
namespace memory
{

Eeprom::Eeprom()
    : currentAddress_(0),
      logger_("EEPROM")
{
}
void Eeprom::write(std::size_t address, const gsl::span<const uint32_t>& data)
{
    UNUSED(address, data);
}

const gsl::span<const uint32_t> Eeprom::read(const uint32_t address, const uint32_t size) const
{
    UNUSED(address, size);
    return gsl::span<const uint32_t>{};
}

} // namespace memory
} // namespace hal
