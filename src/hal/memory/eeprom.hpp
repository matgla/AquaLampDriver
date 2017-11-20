#pragma once

#include <gsl/span>

#include "utils.hpp"

namespace hal
{
namespace memory
{

class Eeprom
{
public:
    Eeprom();
    void write(std::size_t address, const gsl::span<const u8>& data);
    const gsl::span<const u8>& read() const;
}

} // namespace memory
} // namespace hal
