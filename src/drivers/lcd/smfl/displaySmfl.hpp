#pragma once

#include "drivers/lcd/displayDriver.hpp"
#include "logger/Logger.hpp"

namespace drivers
{
namespace lcd
{

class DisplaySmfl : public DisplayDriver
{
public:
    DisplaySmfl(bsp::Board& board);

    void sendData(const gsl::span<const u8>& buffer) override;

protected:
    void reset() override;
    void sendCommand(u8 cmd) override;

    logger::Logger logger_;
};

} // namespace lcd
} // namespace drivers
