#include "drivers/interfaces/onewire.hpp"

#include "containers/staticVector.hpp"
#include "hal/time/sleep.hpp"

namespace drivers
{
namespace interfaces
{

template <std::size_t NumberOfDevices>
OneWire<NumberOfDevices>::OneWire(bsp::Board& board)
    : board_(board),
      logger_("OneWire")
{
}

template <std::size_t NumberOfDevices>
InterfaceStates OneWire<NumberOfDevices>::reset()
{
    logger_.debug() << "reset";
    board_.oneWire.setAsOutput();
    board_.oneWire.setState(bsp::BusState::Low);
    hal::time::usleep(500);

    board_.oneWire.setAsInput();
    hal::time::usleep(70);
    // device detected
    if (bsp::BusState::Low == board_.oneWire.getState())
    {
        hal::time::msleep(1);
        if (bsp::BusState::High == board_.oneWire.getState())
        {
            logger_.debug() << "Device pulse detected";
            return InterfaceStates::Detected;
        }
        // bus must be in high state now, but is not
        logger_.debug() << "Error on bus";

        return InterfaceStates::BusError;
    }
    // any device answered
    logger_.debug() << "No devices on bus";

    return InterfaceStates::NotDetected;
}

template <std::size_t NumberOfDevices>
void OneWire<NumberOfDevices>::write(const u8 byte)
{
    for (u8 i = 0; i < 8; ++i)
    {
        if (byte & (0x01 << i))
        {
            writeBit(Bit::High);
        }
        else
        {
            writeBit(Bit::Low);
        }
    }
}

template <std::size_t NumberOfDevices>
u8 OneWire<NumberOfDevices>::read()
{
    u8 byte = 0;
    for (u8 i = 0; i < 8; ++i)
    {
        if (Bit::High == readBit())
        {
            byte |= (0x01 << i);
        }
    }
    return byte;
}

template <std::size_t NumberOfDevices>
Bit OneWire<NumberOfDevices>::readBit()
{
    Bit bit = Bit::Low;
    board_.oneWire.setAsOutput();
    board_.oneWire.setState(bsp::BusState::Low);
    hal::time::usleep(3);
    board_.oneWire.setAsInput();
    hal::time::usleep(10);
    if (bsp::BusState::High == board_.oneWire.getState())
    {
        bit = Bit::High;
    }
    hal::time::usleep(70);
    return bit;
}

template <std::size_t NumberOfDevices>
void OneWire<NumberOfDevices>::writeBit(const Bit& bit)
{
    board_.oneWire.setAsOutput();
    board_.oneWire.setState(bsp::BusState::Low);
    if (Bit::High == bit)
    {
        // transmit "1"
        hal::time::usleep(15);
        board_.oneWire.setAsInput();
        hal::time::usleep(70);
    }
    else
    {
        // transmit "0"
        hal::time::usleep(70);
        board_.oneWire.setAsInput();
        hal::time::usleep(15);
    }
}

/*
    00110101
    11011101
    11010111
    11111111

    conflicts: []
    */


// TODO: dodać sprawdzenie czy konflikt juz jest w tablicy, jak jest w tablicy i nie jest ostatni to "0"

/*
    1: 00 konflikt, nie ma pozycji konfliktowych
    wrzucam do tablicy pozycje 0
    [0]
    biore 0, odpadaja te z 1
    2...
    to do konca zostaje odczytane bez konfliktow: 1 [00110101]
    [0]
    3.
    konflikt,
    czy jest ostatni?
    tak
    usuwam z tablicy i biore 1
    []
    4.11
    konflikt
    tablica pusta
    [2], biore 0
    1101
    konflikt
    czy ostatni w tablicy?
    nie
    wiec dodaje
    i biore 0
    11010
    [2, 4]
    to dokonca leci
                    2. [11010111]
    [2, 4]
    5. konflikt ostatni biore 1, [11011101]
    6



*/
template <std::size_t NumberOfDevices>
InterfaceStates OneWire<NumberOfDevices>::performAutodetection()
{
    // number of conflicts = number of devices always
    char buffer[5];
    utils::itoa(NumberOfDevices, buffer, 5);
    logger_.debug() << "Performing autodetection: " << buffer;

    containers::StaticVector<u8, NumberOfDevices> conflictPositions;
    for (std::size_t deviceIndex = 0; deviceIndex < NumberOfDevices; ++deviceIndex)
    {
        const auto status = reset();
        u64& address      = devicesAddresses_[deviceIndex];
        if (InterfaceStates::Detected != status)
        {
            return status;
        }

        logger_.debug() << "Searching address";
        write(SEARCH_ROM);

        for (u8 i = 0; i < 64; ++i)
        {
            // read bit
            if (Bit::High == readBit())
            {
                // read complementary bit
                if (Bit::High == readBit())
                {
                    logger_.error() << "No device on bus";
                    return InterfaceStates::NoDevicesOnBus;
                }
                address |= 0x01;
                writeBit(Bit::High);
            }
            else // got "0"
            {
                // read complementary bit
                if (Bit::Low == readBit())
                {
                    // whops, we got conflict
                    // teraz trzeba wybrać 0 czy 1, dodaje pozycje do tablicy konfliktow
                    // sprawdzam czy pozycja juz jest w tablicy konfliktow
                    // jesli jest to ostatni wpis to wybieram "1", bo poprzednim razem wzialem "0",
                    // jesli to jest nie ostatni wpis to biore "0"
                    // conflictsPositions

                    // if some conflicts are known
                    if (conflictPositions.size())
                    {
                        // and if this conflict is last on conflicts lists, this mean that we are
                        // on lowest part of searching tree
                        if (i == conflictPositions.get_last())
                        {
                            // remove last conflict
                            conflictPositions.pop_back();
                            writeBit(Bit::High);
                        }
                        else if (-1 != conflictPositions.find(i))
                        {
                            writeBit(Bit::Low);
                        }
                        else
                        {
                            conflictPositions.push_back(i);
                            writeBit(Bit::Low);
                        }
                    }
                    else
                    {
                        conflictPositions.push_back(i);
                        writeBit(Bit::Low);
                    }
                }
                else
                {
                    writeBit(Bit::Low);
                }
            }
            address = address << 1;
        }
        devicesAddresses_[deviceIndex] = address;
        char buffer[40];
        utils::itoa(address, buffer, 16);
        logger_.debug() << "Found 0x" << buffer;
    }
    return InterfaceStates::Detected;
}

} // namespace drivers
} // namespace interfaces
