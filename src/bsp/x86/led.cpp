#include "bsp/led.hpp"

#include <iostream>

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
    std::cout << "Led on" << std::endl;
}

template <>
void Led<Leds::Led1>::off()
{
    std::cout << "Led off" << std::endl;
}

} // namespace bsp