#pragma once

#include <array>

#include "bsp/board.hpp"

namespace drivers
{
namespace interfaces
{

enum class InterfaceStates : u8
{
    Detected,
    NotDetected,
    BusError,
    NoDevicesOnBus
};

enum class Bit : u8
{
    High,
    Low
};

template <std::size_t NumberOfDevices>
class OneWire
{
public:
    OneWire(bsp::Board& board);
    InterfaceStates reset();
    void write(const u8 byte);
    u8 read();
    Bit readBit();
    void writeBit(const Bit& bit);

    InterfaceStates performAutodetection();

private:
    static_assert(sizeof(u64) >= 8, "Address variable must be 8 byte minimum");

    bsp::Board board_;

    std::array<u64, NumberOfDevices> devicesAddresses_;
};

} // namespace drivers
} // namespace interfaces

#include "drivers/interfaces/onewireImpl.hpp"
