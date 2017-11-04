#include "bsp/led.hpp"

#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "bsp/x86/window.hpp"

namespace bsp
{

template <>
Led<Leds::Led1>::Led()
{
    std::cout << "Led init" << std::endl;
}

template <>
void Led<Leds::Led1>::on()
{
    std::unique_ptr<sf::Shape> shape(new sf::CircleShape(5));
    shape->setFillColor(sf::Color(100, 250, 50));
    shape->setPosition(2, bsp::x86::Window::get().getHeight());
    x86::Window::get().add("LED1", std::move(shape));
}

template <>
void Led<Leds::Led1>::off()
{
    std::unique_ptr<sf::Shape> shape(new sf::CircleShape(5));
    shape->setFillColor(sf::Color(0, 250, 50));
    shape->setPosition(2, bsp::x86::Window::get().getHeight());
    x86::Window::get().add("LED1", std::move(shape));
}

} // namespace bsp