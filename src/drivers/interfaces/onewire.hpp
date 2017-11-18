#pragma once

#include <array>

#include "bsp/board.hpp"

//================
//| ROM COMMANDS |
//================
#define READ_ROM     0x33
#define MATCH_ROM    0x55
#define SKIP_ROM     0xCC
#define ALARM_SEARCH 0xec
#define SEARCH_ROM 0xf0


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

    template <std::size_t DeviceNumber>
    InterfaceStates initTranssmisionWithDevice()
    {
        static_assert(DeviceNumber < NumberOfDevices, "Trying to read from not existing device");
        const auto status = reset();
        if (InterfaceStates::Detected != status)
        {
            return status;
        }

        write(MATCH_ROM);
        write(static_cast<u8>(devicesAddresses_[DeviceNumber] >> 32));
        write(static_cast<u8>(devicesAddresses_[DeviceNumber] & 0x00ff));
    }

private:
    static_assert(sizeof(u64) >= 8, "Address variable must be 8 byte minimum");

    bsp::Board board_;

    std::array<u64, NumberOfDevices> devicesAddresses_;
};

} // namespace drivers
} // namespace interfaces

#include "drivers/interfaces/onewireImpl.hpp"
