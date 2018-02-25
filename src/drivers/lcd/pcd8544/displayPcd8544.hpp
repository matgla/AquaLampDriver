#pragma once

#include <array>

#include "display/colors.hpp"
#include "drivers/lcd/displayDriver.hpp"

#include "bsp/board.hpp"
#include "logger/logger.hpp"

#define PCD8544_SCREEN_HEIGHT 48
#define PCD8544_SCREEN_WIDTH 84

namespace drivers
{
namespace lcd
{

class DisplayPcd8544 : public DisplayDriver
{
public:
    DisplayPcd8544(bsp::Board& board);

    void display() override;
    int getHeight() const override;
    int getWidth() const override;
    void setPixel(int x, int y, display::Colors color = display::Colors::BLACK) override;

protected:
    void reset();
    void sendCommand(u8 cmd);

    bsp::Board& board_;
    logger::Logger logger_;
    std::array<u8, 6 * PCD8544_SCREEN_WIDTH> buffer_;
    std::array<u8, 6 * PCD8544_SCREEN_WIDTH> previous_;
};

} // namespace drivers
} // namespace lcd
