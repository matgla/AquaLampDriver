#pragma once

namespace hal
{
namespace gpio
{

enum class PinMode
{
    OutputPushPull,
    AlternativeFunction,
};

template <class PinName>
class Pin
{
public:
    Pin();

    void high();
    void low();

    bool isHigh();
    bool isLow();

    void setType(const PinMode& mode);
};

} // namespace gpio
} // namespace hal
