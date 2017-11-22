#pragma once

#include <array>

#include "bsp/board.hpp"
#include "logger/logger.hpp"
#include "serializer/serializer.hpp"
//================
//| ROM COMMANDS |
//================
constexpr u8 READ_ROM     = 0x33;
constexpr u8 MATCH_ROM    = 0x55;
constexpr u8 SKIP_ROM     = 0xCC;
constexpr u8 ALARM_SEARCH = 0xec;
constexpr u8 SEARCH_ROM   = 0xf0;


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
    template <typename Type>
    void write(const Type byte)
    {
        u8 data[sizeof(Type)];
        serializer::serialize(data, byte);

        for (u8 byte : data)
        {
            write(byte);
        }
    }

    u8 read();
    Bit readBit();
    void writeBit(const Bit& bit);

    InterfaceStates performAutodetection();

    InterfaceStates initTranssmisionWithDevice(u8 deviceNumber)
    {
        HAL_ASSERT_MSG(deviceNumber < NumberOfDevices, "Trying to read from not existing device");
        const auto status = reset();
        if (InterfaceStates::Detected != status)
        {
            return status;
        }

        write(MATCH_ROM);
        write(devicesAddresses_[deviceNumber]);
    }

private:
    static_assert(sizeof(u64) >= 8, "Address variable must be 8 byte minimum");

    bsp::Board board_;
    logger::Logger logger_;
    std::array<u64, NumberOfDevices> devicesAddresses_;
};

} // namespace drivers
} // namespace interfaces

#include "drivers/interfaces/onewireImpl.hpp"
