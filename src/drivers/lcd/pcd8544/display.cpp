#include "drivers/lcd/display.hpp"

#include "drivers/lcd/font.hpp"

#include "utils.hpp"

namespace drivers
{
namespace lcd
{

font* usedFont = &font_5x7;

Display::Display()
    : logger_("Display")
{
}

void Display::clear(Colors color)
{
    UNUSED(color);
}

void Display::incrementCursorX(u8 offsetX, u8 offsetY)
{
    UNUSED(offsetX, offsetY);
}

void Display::incrementCursorX(u8 offsetX)
{
    UNUSED(offsetX);
}

void Display::incrementCursorY(u8 offsetY)
{
    UNUSED(offsetY);
}

void Display::print(char c, Colors color)
{
    UNUSED(c, color);
}

void Display::print(const char* str, Colors color)
{
    UNUSED(str, color);
}

void Display::setCursor(u8 x, u8 y)
{
    UNUSED(x, y);
}

void Display::setX(u8 x)
{
    UNUSED(x);
}

void Display::setY(u8 y)
{
    UNUSED(y);
}

void Display::drawImage(const gsl::span<const u8>& buffer, u8 width, u8 height, Colors color)
{
    UNUSED(buffer, width, height, color);
}

void Display::drawImage(const gsl::span<const u8>& buffer, u8 width, u8 height, u8 x, u8 y, Colors color)
{
    UNUSED(buffer, width, height, x, y, color);
}

void Display::drawImage(const Image& image, Colors color)
{
    UNUSED(image, color);
}

void Display::drawImage(const Image& image, u8 x, u8 y, Colors color)
{
    UNUSED(image, x, y, color);
}


} // namespace lcd
} // namespace drivers
