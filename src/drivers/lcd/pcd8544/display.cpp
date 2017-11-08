#include "drivers/lcd/display.hpp"

#include "drivers/lcd/font.hpp"

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
}

void Display::incrementCursorX(u8 offsetX, u8 offsetY)
{
}

void Display::incrementCursorX(u8 offsetX)
{
}

void Display::incrementCursorY(u8 offsetY)
{
}

void Display::print(char c, Colors color)
{
}

void Display::print(const char* str, Colors color)
{
}

void Display::setCursor(u8 x, u8 y)
{
}

void Display::setX(u8 x)
{
}

void Display::setY(u8 y)
{
}

void Display::drawImage(const gsl::span<const u8>& buffer, u8 width, u8 height, Colors color)
{
}

void Display::drawImage(const gsl::span<const u8>& buffer, u8 width, u8 height, u8 x, u8 y, Colors color)
{
}

void Display::drawImage(const Image& image, Colors color)
{
}

void Display::drawImage(const Image& image, u8 x, u8 y, Colors color)
{
}


} // namespace lcd
} // namespace drivers
