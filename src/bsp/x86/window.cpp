#include "bsp/x86/window.hpp"
#include <iostream>

#define WINDOW_HEIGHT 100
#define WINDOW_WIDTH 84
#define WINDOW_SCALE 4

namespace bsp
{
namespace x86
{

static sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "AquaLampDriver");

Window::Window()
{
}

Window& Window::get()
{
    static Window w;
    bsp::x86::window.setSize(sf::Vector2u(WINDOW_HEIGHT * WINDOW_SCALE, WINDOW_WIDTH * WINDOW_SCALE));
    return w;
}

int Window::getHeight()
{
    return bsp::x86::window.getSize().y / WINDOW_SCALE;
}

int Window::getWidth()
{
    return bsp::x86::window.getSize().x / WINDOW_SCALE;
}

void Window::setDisplayBox(const sf::RectangleShape& displayBox)
{
    displayBox_ = displayBox;
}

void Window::setDisplay(const sf::Texture& display)
{
    display_ = display;
}

void Window::add(const std::string& name, std::unique_ptr<sf::Shape> shape)
{
    shapes_[name] = std::move(shape);
}


void Window::run()
{
    bsp::x86::window.clear(sf::Color(155, 155, 155));
    sf::Event event;

    while (bsp::x86::window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            bsp::x86::window.close();
        }
    }

    bsp::x86::window.draw(displayBox_);

    sf::Sprite displaySprite(display_);
    displaySprite.setPosition(2, 2);
    bsp::x86::window.draw(displaySprite);

    for (auto& shape : shapes_)
    {
        bsp::x86::window.draw(*shape.second);
    }
    bsp::x86::window.display();
}

sf::RenderWindow& Window::window()
{
    return bsp::x86::window;
}

} // namespace x86
} // namespace bsp
