#pragma once

namespace bsp
{

enum class Leds
{
    Led1
};

template <Leds led>
class Led
{
  public:
    Led()
    {
        static_assert(sizeof(led) == 0, "Default constructor can't be used");

    }
    
    void on()
    {
        static_assert(sizeof(led) == 0, "Default on can't be used");
    }
    
    void off()
    {
        static_assert(sizeof(led) == 0, "Default off can't be used");
    }
};


} // namespace bsp
