#include "drivers/lcd/sfml/displaySfml.hpp"

#include <cstring>
#include <iostream>


#include "bsp/x86/window.hpp"

#define DISPLAY_WIDTH 84
#define DISPLAY_HEIGHT 48

#define PIXEL_OFF_COLOR sf::Color(34, 155, 68)
#define PIXEL_ON_COLOR sf::Color(0, 0, 0)

namespace drivers
{
namespace lcd
{

DisplaySfml::DisplaySfml()
    : logger_("DisplaySmfl")
{
    buffer_.create(DISPLAY_WIDTH, DISPLAY_HEIGHT, PIXEL_OFF_COLOR);
    display();
}

void DisplaySfml::display() const
{
    sf::Texture texture;
    texture.loadFromImage(buffer_);

    sf::RectangleShape rectangle(sf::Vector2f(DISPLAY_WIDTH + 4, DISPLAY_HEIGHT + 4));
    rectangle.setFillColor(sf::Color(1, 1, 1));

    bsp::x86::Window::get().setDisplayBox(rectangle);
    bsp::x86::Window::get().setDisplay(texture);
}

u16 DisplaySfml::getHeight() const
{
    return DISPLAY_HEIGHT;
}

u16 DisplaySfml::getWidth() const
{
    return DISPLAY_WIDTH;
}

void DisplaySfml::setPixel(u16 x, u16 y, display::Colors color)
{
    buffer_.setPixel(x, y, convertToSfColor(color));
}

sf::Color DisplaySfml::convertToSfColor(display::Colors color)
{
    switch (color)
    {
        case display::Colors::BLACK:
            return PIXEL_ON_COLOR;
            break;

        case display::Colors::WHITE:
            return sf::Color(255, 255, 255);
            break;

        case display::Colors::OFF:
            return PIXEL_OFF_COLOR;
            break;
    }
    return PIXEL_OFF_COLOR;
}

} // namespace lcd
} // namespace drivers
