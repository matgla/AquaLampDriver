#include "drivers/lcd/pcd8544/displayPcd8544.hpp"

#include <cmath>

#include "utils.hpp"

#include "display/font.hpp"
#include "hal/time/sleep.hpp"

#include <cstdio>

#define FUNCTION_SET 0x20
#define POWER_UP 0x04
#define POWER_DOWN 0x00
#define VERTICAL_ADDRESSING 0x02
#define HORIZONTAL_ADDRESSING 0x02
#define EXTENDED_INSTRUCTION_SET 0x01
#define BASIC_INSTRUCTION_SET 0x00

// extended instruction set
#define TEMPERATURE_COEFFICIENT_0 0x04
#define TEMPERATURE_COEFFICIENT_1 0x05
#define TEMPERATURE_COEFFICIENT_2 0x06
#define TEMPERATURE_COEFFICIENT_3 0x07

#define BIAS_0 0x10
#define BIAS_1 0x11
#define BIAS_2 0x12
#define BIAS_3 0x13
#define BIAS_4 0x14
#define BIAS_5 0x15
#define BIAS_6 0x16
#define BIAS_7 0x17

#define SET_VOP 0x80

// basic instruction set
#define DISPLAY_BLANK 0x08
#define DISPLAY_NORMAL 0x0c
#define DISPLAY_ALL_SEGMENTS_ON 0x09
#define DISPLAY_INVERSE 0x0d

// 0 <= Y <= 5
#define SET_Y_ADDRESS 0x40
#define SET_X_ADDRESS 0x80

namespace drivers
{
namespace lcd
{

DisplayPcd8544::DisplayPcd8544(bsp::Board& board)
    : board_(board), logger_("Display")
{
    board_.spi.resetPinHigh();
    board_.spi.cePinHigh();

    reset();

    sendCommand(FUNCTION_SET | EXTENDED_INSTRUCTION_SET);
    sendCommand(BIAS_3);
    sendCommand(SET_VOP | 0xcc);
    sendCommand(FUNCTION_SET | BASIC_INSTRUCTION_SET);
    sendCommand(DISPLAY_NORMAL);

    logger_.info() << "Display initalized";
}

void DisplayPcd8544::display()
{
    for (std::size_t i = 0; i < buffer_.size(); ++i)
    {
        if (buffer_[i] != previous_[i])
        {
            u8 y = floor(i / getWidth());
            board_.spi.cePinHigh();
            sendCommand(SET_Y_ADDRESS | y);
            sendCommand(SET_X_ADDRESS | (i - y * getWidth()));
            board_.spi.dcPinHigh();
            board_.spi.cePinLow();

            board_.spi.send(buffer_[i]);
            previous_[i] = buffer_[i];
        }
    }
    board_.spi.cePinHigh();
}

u16 DisplayPcd8544::getHeight() const
{
    return PCD8544_SCREEN_HEIGHT;
}

u16 DisplayPcd8544::getWidth() const
{
    return PCD8544_SCREEN_WIDTH;
}

void DisplayPcd8544::setPixel(u16 x, u16 y, display::Colors color)
{
    if (y >= getHeight() || x >= getWidth())
    {
        logger_.error() << "Trying to set pixel outside buffer setPixel("
                        << x << ", " << y << "), where display(" << getWidth()
                        << ", " << getHeight() << ")!";
        return;
    }

    u16 lineAddress = floor(y / 8) * getWidth() + x;
    u8 pixelMask    = 0x01 << y % 8;

    if (color == display::Colors::OFF)
    {
        buffer_[lineAddress] &= ~pixelMask;
    }
    else
    {
        buffer_[lineAddress] |= pixelMask;
    }
}


void DisplayPcd8544::reset()
{
    board_.spi.resetPinLow();
    hal::time::msleep(1);
    board_.spi.resetPinHigh();
}


void DisplayPcd8544::sendCommand(u8 cmd)
{
    board_.spi.dcPinLow();
    board_.spi.cePinLow();
    board_.spi.send(cmd);
    board_.spi.cePinHigh();
}

} // namespace lcd
} // namespace drivers
