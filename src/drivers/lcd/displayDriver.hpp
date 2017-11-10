#pragma once

#include <gsl/span>

#include "bsp/board.hpp"
#include "drivers/lcd/font.hpp"
#include "drivers/lcd/icons.hpp"
#include "logger/logger.hpp"
#include "utils/types.hpp"

namespace drivers
{
namespace lcd
{

class DisplayDriver
{
public:
    DisplayDriver(bsp::Board& board);
    virtual ~DisplayDriver() = default;
    virtual void sendData(const gsl::span<const u8>& buffer) = 0;

protected:
    virtual void reset() = 0;
    virtual void sendCommand(u8 cmd) = 0;

    bsp::Board& board_;
};

} // namespace lcd
} // namespace drivers
