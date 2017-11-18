#include <gtest/gtest.h>

#include "bsp/board.hpp"
#include "drivers/interfaces/onewire.hpp"

namespace drivers
{
namespace interfaces
{

class OneWireTests : public ::testing::Test
{
public:
    OneWireTests()
        : bus_(board_)
    {
    }

    void SetUp() override
    {
    }

    void TearDown() override
    {
    }


protected:
    bsp::Board board_;
    OneWire<4> bus_;
};

TEST_F(OneWireTests, writeBit)
{
}

} // namespace devices
} // namespace drivers
