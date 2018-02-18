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
}

template <>
void Led<Leds::Led1>::off()
{
}

template <>
Led<Leds::LcdBacklight>::Led()
{
    // TODO: implement
}

template <>
void Led<Leds::LcdBacklight>::on()
{
    // TODO: implement
}

template <>
void Led<Leds::LcdBacklight>::off()
{
    // TODO: implement
}
} // namespace bsp