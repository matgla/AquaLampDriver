#include "bsp/button.hpp"

#include <SFML/Window/Keyboard.hpp>

namespace bsp
{

template <>
Button<Buttons::Left>::Button()
{
}

template <>
Button<Buttons::Right>::Button()
{
}

template <>
Button<Buttons::Up>::Button()
{
}

template <>
Button<Buttons::Down>::Button()
{
}

template <>
Button<Buttons::Back>::Button()
{
}

template <>
Button<Buttons::Select>::Button()
{
}

template <>
bool Button<Buttons::Left>::isPinPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
}

template <>
bool Button<Buttons::Right>::isPinPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
}

template <>
bool Button<Buttons::Up>::isPinPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
}

template <>
bool Button<Buttons::Down>::isPinPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
}

template <>
bool Button<Buttons::Back>::isPinPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace);
}

template <>
bool Button<Buttons::Select>::isPinPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Return);
}

} // namespace bsp