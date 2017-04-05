#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "buffer.hpp"

class BufferTests : public ::testing::Test
{
    virtual void SetUp() {}
    virtual void TearDown()
    {
    }
};

TEST_F(BufferTests, storeTwoValuesBufferOne)
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

TEST_F(BufferTests, bufferThreeValues)
{
    const u8 FIRST_VALUE = 8;
    const u8 SECOND_VALUE = 14;
    const u8 THIRD_VALUE = 89;

    Buffer<4> buffer;

    EXPECT_EQ(0, buffer.size());

    buffer.write(FIRST_VALUE);
    EXPECT_EQ(1, buffer.size());
    
    buffer.write(SECOND_VALUE);
    EXPECT_EQ(2, buffer.size());

    buffer.write(THIRD_VALUE);
    EXPECT_EQ(3, buffer.size());
    
    EXPECT_EQ(FIRST_VALUE, buffer.getByte());
    EXPECT_EQ(2, buffer.size());

    EXPECT_EQ(SECOND_VALUE, buffer.getByte());
    EXPECT_EQ(1, buffer.size());

    EXPECT_EQ(THIRD_VALUE, buffer.getByte());
    EXPECT_EQ(0, buffer.size());
}

TEST_F(BufferTests, cycleOldValuesShouldBeOverridenReadFromBegin)
{
    const u8 FIRST_VALUE = 8;
    const u8 SECOND_VALUE = 14;
    const u8 THIRD_VALUE = 89;
    const u8 FOURTH_VALUE = 12;

    Buffer<3> buffer;

    EXPECT_EQ(0, buffer.size());
    buffer.write(FIRST_VALUE);
    EXPECT_EQ(1, buffer.size());
    buffer.write(SECOND_VALUE);
    EXPECT_EQ(2, buffer.size());
    buffer.write(THIRD_VALUE);
    EXPECT_EQ(3, buffer.size());
    buffer.write(FOURTH_VALUE);
    EXPECT_EQ(3, buffer.size());

    EXPECT_EQ(SECOND_VALUE, buffer.getByte());
    EXPECT_EQ(THIRD_VALUE, buffer.getByte());
    EXPECT_EQ(FOURTH_VALUE, buffer.getByte());
}

TEST_F(BufferTests, cycleWhenReaderInMid)
{
    const u8 FIRST_VALUE = 8;
    const u8 SECOND_VALUE = 14;
    const u8 THIRD_VALUE = 89;
    const u8 FOURTH_VALUE = 12;
    const u8 FIFTH_VALUE = 10;
    const u8 SIXTH_VALUE = 12;

    Buffer<3> buffer;

    EXPECT_EQ(0, buffer.size());
    buffer.write(FIRST_VALUE);
    EXPECT_EQ(1, buffer.size());
    buffer.write(SECOND_VALUE);

    EXPECT_EQ(FIRST_VALUE, buffer.getByte());
    EXPECT_EQ(SECOND_VALUE, buffer.getByte());
    EXPECT_EQ(0, buffer.size());
    
    buffer.write(THIRD_VALUE);
    EXPECT_EQ(1, buffer.size());
    buffer.write(FOURTH_VALUE);
    EXPECT_EQ(2, buffer.size());
    buffer.write(FIFTH_VALUE);
    EXPECT_EQ(3, buffer.size());
    buffer.write(SIXTH_VALUE);
    EXPECT_EQ(3, buffer.size());

    EXPECT_EQ(FOURTH_VALUE, buffer.getByte());
    EXPECT_EQ(FIFTH_VALUE, buffer.getByte());
    EXPECT_EQ(SIXTH_VALUE, buffer.getByte());
}

TEST_F(BufferTests, RemoveFromBeginOfBuffer)
{
    char INITIAL_BUFFER[] = "ABC\0";
    Buffer<3> buffer;

    buffer.write(INITIAL_BUFFER);
    EXPECT_EQ(buffer.size(), 3);
    
    buffer.removeFromBuffer(0);
    EXPECT_EQ(buffer.size(), 2);
    EXPECT_EQ(buffer.getByte(), 'B');
    EXPECT_EQ(buffer.getByte(), 'C');
}

TEST_F(BufferTests, RemoveFromBuffer)
{
    char INITIAL_BUFFER[] = "ABCDE\0";
    Buffer<5> buffer;

    buffer.write(INITIAL_BUFFER);
    EXPECT_EQ(buffer.size(), 5);
    
    buffer.removeFromBuffer(1);
    EXPECT_EQ(buffer.size(), 4);
    EXPECT_EQ(buffer.getByte(), 'A');
    buffer.removeFromBuffer(2);
    EXPECT_EQ(buffer.size(), 2);
    EXPECT_EQ(buffer.getByte(), 'C');
    EXPECT_EQ(buffer.getByte(), 'D');
    EXPECT_EQ(buffer.size(), 0);
}

TEST_F(BufferTests, RemoveFromEndOfBuffer)
{
    const char INITIAL_BUFFER[] = "ABCDE\0";
    const char BUFFER_2[] = "FGHIJ\0";
    Buffer<5> buffer;

    buffer.write(INITIAL_BUFFER);
    EXPECT_EQ(buffer.size(), 5);
    
    buffer.removeFromBuffer(5);
    EXPECT_EQ(buffer.getByte(), 'A');
    EXPECT_EQ(buffer.getByte(), 'B');
    EXPECT_EQ(buffer.getByte(), 'C');
    EXPECT_EQ(buffer.getByte(), 'D');
    EXPECT_EQ(buffer.size(), 0);
    buffer.write(BUFFER_2);
   // buffer.removeFromBuffer(2);
    EXPECT_EQ(buffer.getByte(), 'F');
    EXPECT_EQ(buffer.getByte(), 'G');
    EXPECT_EQ(buffer.getByte(), 'H');
    EXPECT_EQ(buffer.getByte(), 'I');
    EXPECT_EQ(buffer.getByte(), 'J');
    EXPECT_EQ(buffer.size(), 0);
}