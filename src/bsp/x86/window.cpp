#include "bsp/x86/window.hpp"
#include <iostream>

#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 480
#define WINDOW_SCALE 6

namespace bsp
{
namespace x86
{

static sf::RenderWindow window(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), "AquaLampDriver");

Window::Window()
{
    std::cout << "Created SMFL window" << std::endl;
}

Window& Window::get()
{
    static Window w;
    return w;
}

int Window::getHeight()
{
    return bsp::x86::window.getSize().y;
}

int Window::getWidth()
{
    return bsp::x86::window.getSize().x;
}

void Window::setDisplayBox(const sf::RectangleShape& displayBox)
{
    displayBox_ = displayBox;
    displayBox_.setScale(sf::Vector2f{WINDOW_SCALE, WINDOW_SCALE});
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
    displaySprite.setPosition(WINDOW_SCALE, WINDOW_SCALE);
    displaySprite.setScale(sf::Vector2f{WINDOW_SCALE, WINDOW_SCALE});
    bsp::x86::window.draw(displaySprite);

    for (auto& shape : shapes_)
    {
        if (shape.second != nullptr)
        {
            bsp::x86::window.draw(*shape.second);
        }
    }
    bsp::x86::window.display();
}

sf::RenderWindow& Window::window()
{
    return bsp::x86::window;
}

} // namespace x86
} // namespace bsp
