#include "bsp/onewire.hpp"

#include "utils.hpp"

namespace bsp
{

template <>
OneWire<OneWires::OneWire1>::OneWire()
{
}

template <>
void OneWire<OneWires::OneWire1>::setAsInput()
{
}

template <>
void OneWire<OneWires::OneWire1>::setAsOutput()
{
}

template <>
BusState OneWire<OneWires::OneWire1>::getState()
{
    return BusState::Low;
}

template <>
void OneWire<OneWires::OneWire1>::setState(BusState state)
{
    UNUSED(state);
}

} // namespace bsp
