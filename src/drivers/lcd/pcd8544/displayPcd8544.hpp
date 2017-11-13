#pragma once

#include <array>

#include "display/colors.hpp"
#include "drivers/lcd/displayDriver.hpp"

#include "bsp/board.hpp"
#include "logger/Logger.hpp"

#define PCD8544_SCREEN_HEIGHT 42
#define PCD8544_SCREEN_WIDTH 82

namespace drivers
{
namespace lcd
{

class DisplayPcd8544 : public DisplayDriver
{
public:
    DisplayPcd8544(bsp::Board& board);

    void display() const override;
    u16 getHeight() const override;
    u16 getWidth() const override;
    void setPixel(u16 x, u16 y, display::Colors color = display::Colors::BLACK) override;

protected:
    void reset();
    void sendCommand(u8 cmd);

    bsp::Board& board_;
    logger::Logger logger_;
    std::array<display::Colors, PCD8544_SCREEN_HEIGHT * PCD8544_SCREEN_WIDTH> buffer_;
};

} // namespace drivers
} // namespace lcd
