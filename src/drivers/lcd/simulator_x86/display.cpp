#include "drivers/lcd/display.hpp"

#include <cstring>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "bsp/x86/window.hpp"
#include "drivers/lcd/font.hpp"

#define PIXEL_OFF_COLOR sf::Color(34, 155, 68)
#define PIXEL_ON_COLOR sf::Color(0, 0, 0)

namespace drivers
{
namespace lcd
{

font* usedFont = &font_5x7;

static sf::Image display_;

sf::Color convertToSfColor(Colors color)
{
    switch (color)
    {
        case Colors::BLACK:
            return PIXEL_ON_COLOR;
            break;

        case Colors::WHITE:
            return sf::Color(255, 255, 255);
            break;

        case Colors::OFF:
            return PIXEL_OFF_COLOR;
            break;
    }
    return PIXEL_OFF_COLOR;
}

void drawScreen()
{
    sf::Texture texture;
    texture.loadFromImage(display_);

    sf::RectangleShape rectangle(sf::Vector2f(DISPLAY_WIDTH + 4, DISPLAY_HEIGHT + 4));
    rectangle.setFillColor(sf::Color(1, 1, 1));

    bsp::x86::Window::get().setDisplayBox(rectangle);
    bsp::x86::Window::get().setDisplay(texture);
}

Display::Display()
    : logger_("Display")
{
    display_.create(DISPLAY_WIDTH, DISPLAY_HEIGHT, PIXEL_OFF_COLOR);
    clear(Colors::OFF);
    drawScreen();
}

void Display::clear(Colors color)
{
    for (int y = 0; y < DISPLAY_HEIGHT; ++y)
    {
        for (int x = 0; x < DISPLAY_WIDTH; ++x)
        {
            display_.setPixel(x, y, convertToSfColor(color));
        }
    }
    cursorPosition_.x = 0;
    cursorPosition_.y = 0;
}

void Display::incrementCursorX(u8 offsetX, u8 offsetY)
{
    if (cursorPosition_.x + offsetX >= DISPLAY_WIDTH)
    {
        cursorPosition_.y += offsetY;
        cursorPosition_.x = 0;
    }
    else
    {
        cursorPosition_.x += offsetX;
    }
}

void Display::incrementCursorX(u8 offsetX)
{
    if (cursorPosition_.x + offsetX >= DISPLAY_WIDTH)
    {
        cursorPosition_.y += usedFont->height;
        cursorPosition_.x = 0;
    }
    else
    {
        cursorPosition_.x += offsetX;
    }
}

void Display::incrementCursorY(u8 offsetY)
{
    if (cursorPosition_.y + offsetY >= DISPLAY_HEIGHT)
    {
        cursorPosition_.y = offsetY;
        cursorPosition_.x = 0;
    }
    else
    {
        cursorPosition_.y += offsetY;
    }
}

void Display::print(char c, Colors color)
{
    u16 charOffset = c - 32; // 32 first letter in font
    u16 charPosition = charOffset + charOffset * (usedFont->width - 1);

    const uint8_t* font_ptr = &usedFont->array[charPosition];

    if (c == 0xA)
    {
        cursorPosition_.x = 0;
        cursorPosition_.y += usedFont->height + 1;
        return;
    }

    else if (c == 0x08)
    {
        cursorPosition_.x -= (usedFont->width + 1);
        c = ' ';
    }

    int i = 0;

    for (i = cursorPosition_.x; i < usedFont->width + cursorPosition_.x; i++)
    {
        for (int j = usedFont->height; j > 0; j--)
        {
            if ((*font_ptr >> j) & 0x01)
            {
                if (i < DISPLAY_WIDTH && (cursorPosition_.y + usedFont->height - j) < DISPLAY_HEIGHT)
                {
                    display_.setPixel(i, cursorPosition_.y + usedFont->height - j, convertToSfColor(color));
                }
            }
        }
        ++font_ptr;
    }
    incrementCursorX(usedFont->width + 1, usedFont->height + 1);
    drawScreen();
}

void Display::print(const char* str, Colors color)
{
    for (std::size_t i = 0; i < strlen(str); i++)
    {
        print(str[i], color);
    }
}

void Display::setCursor(u8 x, u8 y)
{
    cursorPosition_.x = x;
    cursorPosition_.y = y;
}

void Display::setX(u8 x)
{
    cursorPosition_.x = x;
}

void Display::setY(u8 y)
{
    cursorPosition_.y = y;
}

void Display::drawImage(const gsl::span<const u8>& buffer, u8 width, u8 height, Colors color)
{
    UNUSED(color);
    if (buffer.length() < width || sizeof(buffer[0]) * 8 < height)
    {
        logger_.error() << "Buffer smaller than picture";
        logger_.error() << "buffer.length()=" << buffer.length() << ", width=" << width << ", sizeof(buffer[0])=" << sizeof(buffer[0]) << ", height=" << height;
        return;
    }

    int i = 0;
    for (int x = cursorPosition_.x; x < cursorPosition_.x + width; ++x)
    {
        for (int y = height; y > 0; --y)
        {
            if ((buffer[i] >> y) & 0x01)
            {
                if (x < DISPLAY_WIDTH && (cursorPosition_.y + height - y) < DISPLAY_HEIGHT)
                {
                    display_.setPixel(x, cursorPosition_.y + height - y, convertToSfColor(color));
                }
            }
        }
        i++;
    }

    incrementCursorX(width, usedFont->height);
    drawScreen();
}

void Display::drawImage(const gsl::span<const u8>& buffer, u8 width, u8 height, u8 x, u8 y, Colors color)
{
    UNUSED(color);
    cursorPosition_.x = x;
    cursorPosition_.y = y;
    drawImage(buffer, width, height);
}

void Display::drawImage(const Image& image, Colors color)
{
    UNUSED(color);
    drawImage(image.data, image.width, image.height);
}

void Display::drawImage(const Image& image, u8 x, u8 y, Colors color)
{
    UNUSED(color);
    cursorPosition_.x = x;
    cursorPosition_.y = y;
    drawImage(image);
}


} // namespace lcd
} // namespace drivers
