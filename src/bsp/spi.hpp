#pragma once

#include "utils/types.hpp"

namespace bsp
{
class Spi
{
public:
    Spi();
    u8 send(const u8 byte) const;
    void resetPinHigh() const;
    void resetPinLow() const;
    void dcPinHigh() const;
    void dcPinLow() const;
    void cePinHigh() const;
    void cePinLow() const;
};

}
