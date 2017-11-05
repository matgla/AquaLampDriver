#include "drivers/lcd/display.hpp"

#include <cstring>

#include <SFML/Graphics.hpp>

#include "bsp/x86/window.hpp"
#include "drivers/lcd/font.hpp"

#define PIXEL_OFF_COLOR sf::Color(34, 155, 68)
#define PIXEL_ON_COLOR sf::Color(0, 0, 0)

// font font_5x8;

static font* use_font;

namespace drivers
{
namespace lcd
{

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
    use_font = &font_5x8;
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

void Display::print(char c, Colors color)
{
    const uint8_t* font_ptr = &use_font->array[(c - 32) + (c - 32) * (use_font->height - 1)];

    if (cursorPosition_.x + use_font->width >= DISPLAY_WIDTH)
    {
        cursorPosition_.y += use_font->height + 2;
        cursorPosition_.x = 0;
    }

    if (cursorPosition_.y + use_font->height >= DISPLAY_HEIGHT)
    {
        cursorPosition_.y = use_font->height + 2;
        cursorPosition_.x = 0;
    }

    if (c == 0xA)
    {
        cursorPosition_.x = 0;
        cursorPosition_.y += use_font->height + 2;
        return;
    }

    else if (c == 0x08)
    {
        cursorPosition_.x -= (use_font->width + 2);
        c = ' ';
    }

    int i = 0;

    for (i = cursorPosition_.y; i < use_font->height + cursorPosition_.y; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            if ((*font_ptr >> j) & 0x01)
            {
                display_.setPixel(cursorPosition_.x + 7 - j, i, convertToSfColor(color));
            }
        }
        ++font_ptr;
    }
    cursorPosition_.x += use_font->width + 1;
    drawScreen();
}

void Display::print(const char* str, Colors color)
{
    for (int i = 0; i < strlen(str); i++)
    {
        print(str[i], color);
    }
}

} // namespace lcd
} // namespace drivers
