#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "buffer.hpp"

class ReaderWriterBufferTests : public ::testing::Test
{
    virtual void SetUp()
    {
    }
    virtual void TearDown()
    {
    }
};

TEST_F(ReaderWriterBufferTests, readWrite)
{
    const u8 FIRST_VALUE = 8;
    const u8 SECOND_VALUE = 14;

    Buffer<4> buffer;

    EXPECT_EQ(0, buffer.size());

    buffer.write(FIRST_VALUE);
    EXPECT_EQ(1, buffer.size());
    EXPECT_EQ(FIRST_VALUE, buffer.getByte());

    buffer.write(SECOND_VALUE);
    EXPECT_EQ(1, buffer.size());
    EXPECT_EQ(SECOND_VALUE, buffer.getByte());
}
