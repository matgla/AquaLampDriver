#include <gtest/gtest.h>

#include "utils.hpp"

namespace utils
{

TEST(UtilsTest, ReturnZerosForZero)
{
    float value     = 0;
    float precision = 1;
    EXPECT_EQ(0, floatToInts(value, precision).first);
    EXPECT_EQ(0, floatToInts(value, precision).second);
}

TEST(UtilsTest, ConvertWithSinglePrecision)
{
    const float precision = 1;
    EXPECT_EQ(3, floatToInts(3.14, precision).first);
    EXPECT_EQ(1, floatToInts(3.14, precision).second);

    EXPECT_EQ(0, floatToInts(0.01, precision).first);
    EXPECT_EQ(0, floatToInts(0.01, precision).second);

    EXPECT_EQ(1, floatToInts(1.06, precision).first);
    EXPECT_EQ(1, floatToInts(1.06, precision).second);

    EXPECT_EQ(0, floatToInts(0.29, precision).first);
    EXPECT_EQ(3, floatToInts(0.29, precision).second);
}

TEST(UtilsTest, ConvertWithMorePrecision)
{
    const float precision = 4;
    EXPECT_EQ(3, floatToInts(3.1412, precision).first);
    EXPECT_EQ(1412, floatToInts(3.1412, precision).second);

    EXPECT_EQ(0, floatToInts(0.01234, precision).first);
    EXPECT_EQ(0, floatToInts(0.01234, precision).second);

    EXPECT_EQ(0, floatToInts(0.05000, precision).first);
    EXPECT_EQ(1, floatToInts(0.05000, precision).second);

    EXPECT_EQ(0, floatToInts(0.04999, precision).first);
    EXPECT_EQ(0, floatToInts(0.04999, precision).second);

    EXPECT_EQ(2, floatToInts(2.62348, precision).first);
    EXPECT_EQ(6235, floatToInts(2.62348, precision).second);
}

} // namespace utils
