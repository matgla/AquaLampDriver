#include <gtest/gtest.h>

#include <chrono>
#include <ctime>

#include "app/Context.hpp"
#include "bsp/board.hpp"
#include "controller/sunlightController.hpp"
#include "display/font.hpp"
#include "drivers/lcd/displayDriver.hpp"
#include "utils/types.hpp"

#include <iostream>

class DriverStub : public drivers::lcd::DisplayDriver
{
public:
    void display() override
    {
    }
    u16 getHeight() const override
    {
    }
    u16 getWidth() const override
    {
    }
    void setPixel(u16 x, u16 y, display::Colors color = display::Colors::BLACK) override
    {
    }
};

class TimeStub
{
public:
    TimeStub(std::time_t time = 0)
        : currentTime_(time)
    {
    }

    void incrementTime()
    {
        ++currentTime_;
    }

    template <typename T>
    void forwardTime(const T& duration)
    {
        currentTime_ += std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    }

    void setTime(const std::time_t time)
    {
        currentTime_ = time;
    }

    std::time_t getCurrentTime() const
    {
        return currentTime_;
    }

private:
    std::time_t currentTime_;
};

namespace controller
{

class SunlightControllerShould : public ::testing::Test
{
public:
    SunlightControllerShould()
        : logger_("SunlightControllerTests"),
          display_(board_, driver_, display::font_5x7),
          context_(board_, display_, logger_),
          controller_(context_)
    {
    }

protected:
    bsp::Board board_;
    DriverStub driver_;
    display::Display display_;
    logger::Logger logger_;
    TimeStub time_;
    app::Context context_;
    SunlightController controller_;
};

std::time_t getTime(int hour, int minute, int second)
{
    std::time_t currentTime = std::time(nullptr);
    std::tm* timeData       = localtime(&currentTime);
    timeData->tm_hour       = hour;
    timeData->tm_min        = minute;
    timeData->tm_sec        = second;

    return std::mktime(timeData);
}

TEST_F(SunlightControllerShould, StartInFinishedState)
{
    EXPECT_EQ(SunlightController::State::Finished, controller_.state());
}

TEST_F(SunlightControllerShould, PerformSunrise)
{
    constexpr u8 initialPower = 0;
    constexpr u8 finalPower   = 60;

    constexpr u8 sunriseHour   = 11;
    constexpr u8 sunriseMinute = 1;
    constexpr u8 sunriseSecond = 30;

    constexpr u8 initialHour   = 10;
    constexpr u8 initialMinute = 59;
    constexpr u8 initialSecond = 0;

    constexpr std::time_t sunriseLength = 3600;

    const std::time_t sunriseStartTime = getTime(sunriseHour, sunriseMinute, sunriseSecond);
    context_.currentChannelsSettings().masterPower(initialPower);
    context_.dayChannelsSettings().masterPower(finalPower);

    context_.sunriseSettings().set(sunriseHour, sunriseMinute, sunriseSecond);
    context_.sunriseSettings().length(sunriseLength);

    std::time_t currentTime = getTime(initialHour, initialMinute, initialSecond);
    std::time_t endTime     = sunriseStartTime + sunriseLength;

    EXPECT_EQ(SunlightController::State::Finished, controller_.state());
    for (currentTime; currentTime < sunriseStartTime; ++currentTime)
    {
        controller_.run(currentTime);
    }
    EXPECT_EQ(SunlightController::State::Finished, controller_.state());

    controller_.run(++currentTime);
    EXPECT_EQ(SunlightController::State::Sunrise, controller_.state());

    int part          = sunriseLength / 10;
    int powerPart     = (finalPower - initialPower) / 10;
    int expectedPower = powerPart;
    for (currentTime; currentTime < endTime; ++currentTime)
    {
        controller_.run(currentTime);
        if ((currentTime - sunriseStartTime) % part == 0)
        {
            EXPECT_GE(context_.currentChannelsSettings().masterPower(), expectedPower - 2);
            EXPECT_LE(context_.currentChannelsSettings().masterPower(), expectedPower + 2);
            expectedPower += powerPart;
        }
    }

    EXPECT_EQ(SunlightController::State::Sunrise, controller_.state());

    controller_.run(++currentTime);
    EXPECT_EQ(SunlightController::State::Finished, controller_.state());
    EXPECT_EQ(finalPower, context_.currentChannelsSettings().masterPower());
}

TEST_F(SunlightControllerShould, PerformSunset)
{
    constexpr u8 initialPower = 75;
    constexpr u8 finalPower   = 5;

    constexpr u8 sunsetHour   = 20;
    constexpr u8 sunsetMinute = 0;
    constexpr u8 sunsetSecond = 0;

    constexpr u8 initialHour   = 19;
    constexpr u8 initialMinute = 55;
    constexpr u8 initialSecond = 0;

    constexpr std::time_t sunsetLength = 3600;

    const std::time_t sunsetStartTime = getTime(sunsetHour, sunsetMinute, sunsetSecond);
    context_.currentChannelsSettings().masterPower(initialPower);
    context_.nightChannelsSettings().masterPower(finalPower);

    context_.sunsetSettings().set(sunsetHour, sunsetMinute, sunsetSecond);
    context_.sunsetSettings().length(sunsetLength);

    std::time_t currentTime = getTime(initialHour, initialMinute, initialSecond);
    std::time_t endTime     = sunsetStartTime + sunsetLength;

    EXPECT_EQ(SunlightController::State::Finished, controller_.state());
    for (currentTime; currentTime < sunsetStartTime; ++currentTime)
    {
        controller_.run(currentTime);
    }
    EXPECT_EQ(SunlightController::State::Finished, controller_.state());

    controller_.run(++currentTime);
    EXPECT_EQ(SunlightController::State::Sunset, controller_.state());


    int part          = sunsetLength / 10;
    int powerPart     = (initialPower - finalPower) / 10;
    int expectedPower = initialPower - powerPart;
    for (currentTime; currentTime < endTime; ++currentTime)
    {
        controller_.run(currentTime);
        if ((currentTime - sunsetStartTime) % part == 0)
        {
            EXPECT_GE(context_.currentChannelsSettings().masterPower(), expectedPower - 2);
            EXPECT_LE(context_.currentChannelsSettings().masterPower(), expectedPower + 2);
            expectedPower -= powerPart;
        }
    }

    EXPECT_EQ(SunlightController::State::Sunset, controller_.state());

    controller_.run(++currentTime);
    EXPECT_EQ(SunlightController::State::Finished, controller_.state());
    EXPECT_EQ(finalPower, context_.currentChannelsSettings().masterPower());
}

TEST_F(SunlightControllerShould, SunsetBreaksSunrise)
{
    constexpr u8 initialPower = 5;
    constexpr u8 finalPower   = 5;
    constexpr u8 dayPower     = 80;
    constexpr u8 nightPower   = 10;

    constexpr u8 sunriseHour   = 19;
    constexpr u8 sunriseMinute = 45;
    constexpr u8 sunriseSecond = 0;

    constexpr u8 sunsetHour   = 20;
    constexpr u8 sunsetMinute = 0;
    constexpr u8 sunsetSecond = 0;

    constexpr u8 initialHour   = 19;
    constexpr u8 initialMinute = 15;
    constexpr u8 initialSecond = 0;

    constexpr std::time_t sunriseLength = 3600;
    constexpr std::time_t sunsetLength  = 3600;

    const std::time_t sunsetStartTime  = getTime(sunsetHour, sunsetMinute, sunsetSecond);
    const std::time_t sunriseStartTime = getTime(sunriseHour, sunriseMinute, sunriseSecond);

    context_.currentChannelsSettings().masterPower(initialPower);

    context_.nightChannelsSettings().masterPower(nightPower);
    context_.dayChannelsSettings().masterPower(dayPower);

    context_.sunriseSettings().set(sunriseHour, sunriseMinute, sunriseSecond);
    context_.sunriseSettings().length(sunriseLength);
    context_.sunsetSettings().set(sunsetHour, sunsetMinute, sunsetSecond);
    context_.sunsetSettings().length(sunsetLength);

    std::time_t currentTime = getTime(initialHour, initialMinute, initialSecond);

    EXPECT_EQ(SunlightController::State::Finished, controller_.state());
    for (currentTime; currentTime < sunriseStartTime; ++currentTime)
    {
        controller_.run(currentTime);
    }
    EXPECT_EQ(SunlightController::State::Finished, controller_.state());

    controller_.run(++currentTime);
    EXPECT_EQ(SunlightController::State::Sunrise, controller_.state());

    int part          = sunriseLength / 10;
    int powerPart     = (dayPower - initialPower) / 10;
    int expectedPower = initialPower + powerPart;
    for (currentTime; currentTime < sunsetStartTime; ++currentTime)
    {
        controller_.run(currentTime);
        if ((currentTime - sunriseStartTime) % part == 0)
        {
            EXPECT_GE(context_.currentChannelsSettings().masterPower(), expectedPower - 2);
            EXPECT_LE(context_.currentChannelsSettings().masterPower(), expectedPower + 2);
            expectedPower += powerPart;
        }
    }

    EXPECT_EQ(SunlightController::State::Sunrise, controller_.state());

    controller_.run(++currentTime);
    EXPECT_EQ(SunlightController::State::Sunset, controller_.state());

    part          = sunsetLength / 10;
    powerPart     = (context_.currentChannelsSettings().masterPower() - nightPower) / 10;
    expectedPower = context_.currentChannelsSettings().masterPower() - powerPart;
    for (currentTime; currentTime < sunsetStartTime + sunsetLength; ++currentTime)
    {
        controller_.run(currentTime);
        if ((currentTime - sunsetStartTime) % part == 0)
        {
            EXPECT_GE(context_.currentChannelsSettings().masterPower(), expectedPower - 2);
            EXPECT_LE(context_.currentChannelsSettings().masterPower(), expectedPower + 2);
            expectedPower -= powerPart;
        }
    }

    EXPECT_EQ(SunlightController::State::Sunset, controller_.state());

    controller_.run(++currentTime);
    EXPECT_EQ(SunlightController::State::Finished, controller_.state());


    EXPECT_EQ(nightPower, context_.currentChannelsSettings().masterPower());
}

TEST_F(SunlightControllerShould, PerformFastSunrise)
{
    constexpr u8 initialPower = 10;
    constexpr u8 finalPower   = 90;

    constexpr u8 initialHour   = 0;
    constexpr u8 initialMinute = 0;
    constexpr u8 initialSecond = 12;

    constexpr std::time_t fastSunriseLength = 100;

    context_.currentChannelsSettings().masterPower(initialPower);
    context_.dayChannelsSettings().masterPower(finalPower);
    context_.fastSunriseLength(fastSunriseLength);

    std::time_t currentTime          = getTime(initialHour, initialMinute, initialSecond);
    std::time_t fastSunriseStartTime = currentTime;
    std::time_t endTime              = currentTime + fastSunriseLength;

    EXPECT_EQ(SunlightController::State::Finished, controller_.state());
    controller_.fastSunrise(currentTime);

    EXPECT_EQ(SunlightController::State::FastSunrise, controller_.state());

    int part          = fastSunriseLength / 10;
    int powerPart     = (finalPower - initialPower) / 10;
    int expectedPower = initialPower;
    for (currentTime; currentTime < endTime; ++currentTime)
    {
        controller_.run(currentTime);
        if ((currentTime - fastSunriseStartTime) % part == 0)
        {
            EXPECT_GE(context_.currentChannelsSettings().masterPower(), expectedPower - 2);
            EXPECT_LE(context_.currentChannelsSettings().masterPower(), expectedPower + 2);
            expectedPower += powerPart;
        }
    }

    EXPECT_EQ(SunlightController::State::FastSunrise, controller_.state());
    controller_.run(++currentTime);
    EXPECT_EQ(SunlightController::State::Finished, controller_.state());

    EXPECT_EQ(finalPower, context_.currentChannelsSettings().masterPower());
}

TEST_F(SunlightControllerShould, PerformFastSunriseAgainIfDifferenceMoreThan5)
{
    constexpr u8 initialPower = 10;
    constexpr u8 finalPower   = 90;

    constexpr u8 initialHour   = 0;
    constexpr u8 initialMinute = 0;
    constexpr u8 initialSecond = 12;

    constexpr std::time_t fastSunriseLength = 100;

    context_.currentChannelsSettings().masterPower(initialPower);
    context_.dayChannelsSettings().masterPower(finalPower);
    context_.fastSunriseLength(fastSunriseLength);

    std::time_t currentTime          = getTime(initialHour, initialMinute, initialSecond);
    std::time_t fastSunriseStartTime = currentTime;
    std::time_t endTime              = currentTime + fastSunriseLength;

    EXPECT_EQ(SunlightController::State::Finished, controller_.state());
    controller_.fastSunrise(currentTime);

    EXPECT_EQ(SunlightController::State::FastSunrise, controller_.state());

    int part          = fastSunriseLength / 10;
    int powerPart     = (finalPower - initialPower) / 10;
    int expectedPower = initialPower;
    for (currentTime; currentTime < endTime - fastSunriseLength / 2; ++currentTime)
    {
        controller_.run(currentTime);
        if ((currentTime - fastSunriseStartTime) % part == 0)
        {
            EXPECT_GE(context_.currentChannelsSettings().masterPower(), expectedPower - 2);
            EXPECT_LE(context_.currentChannelsSettings().masterPower(), expectedPower + 2);
            expectedPower += powerPart;
        }
    }

    // make some delay
    currentTime += fastSunriseLength;
    controller_.run(currentTime);
    EXPECT_EQ(SunlightController::State::FastSunrise, controller_.state());
    // perform fast sunrise for rest power
    part          = fastSunriseLength / 10;
    powerPart     = (context_.dayChannelsSettings().masterPower() - context_.currentChannelsSettings().masterPower()) / 10;
    expectedPower = context_.currentChannelsSettings().masterPower();
    endTime       = currentTime + fastSunriseLength;
    for (currentTime; currentTime < endTime; ++currentTime)
    {
        controller_.run(currentTime);
        if ((currentTime - fastSunriseStartTime) % part == 0)
        {
            EXPECT_GE(context_.currentChannelsSettings().masterPower(), expectedPower - 2);
            EXPECT_LE(context_.currentChannelsSettings().masterPower(), expectedPower + 2);
            expectedPower += powerPart;
        }
    }

    EXPECT_EQ(SunlightController::State::FastSunrise, controller_.state());
    controller_.run(++currentTime);
    EXPECT_EQ(SunlightController::State::Finished, controller_.state());

    EXPECT_EQ(finalPower, context_.currentChannelsSettings().masterPower());
}

// TEST_F(SunlightControllerShould, PerformFastSunsetIfDifferenceMoreThan5)
// {
//     constexpr u8 initialPower = 10;
//     constexpr u8 finalPower   = 90;

//     constexpr u8 initialHour   = 0;
//     constexpr u8 initialMinute = 0;
//     constexpr u8 initialSecond = 12;

//     constexpr std::time_t fastSunriseLength = 100;

//     context_.currentChannelsSettings().masterPower(initialPower);
//     context_.dayChannelsSettings().masterPower(finalPower);
//     context_.fastSunriseLength(fastSunriseLength);

//     std::time_t currentTime          = getTime(initialHour, initialMinute, initialSecond);
//     std::time_t fastSunriseStartTime = currentTime;
//     std::time_t endTime              = currentTime + fastSunriseLength;

//     EXPECT_EQ(SunlightController::State::Finished, controller_.state());
//     controller_.fastSunrise(currentTime);

//     EXPECT_EQ(SunlightController::State::FastSunrise, controller_.state());

//     int part          = fastSunriseLength / 10;
//     int powerPart     = (finalPower - initialPower) / 10;
//     int expectedPower = initialPower;
//     for (currentTime; currentTime < endTime - fastSunriseLength / 2; ++currentTime)
//     {
//         controller_.run(currentTime);
//         if ((currentTime - fastSunriseStartTime) % part == 0)
//         {
//             EXPECT_GE(context_.currentChannelsSettings().masterPower(), expectedPower - 2);
//             EXPECT_LE(context_.currentChannelsSettings().masterPower(), expectedPower + 2);
//             expectedPower += powerPart;
//         }
//     }

//     // make some delay
//     currentTime += fastSunriseLength;
//     controller_.run(currentTime);
//     EXPECT_EQ(SunlightController::State::FastSunrise, controller_.state());
//     // perform fast sunrise for rest power
//     part          = fastSunriseLength / 10;
//     powerPart     = (context_.dayChannelsSettings().masterPower() - context_.currentChannelsSettings().masterPower()) / 10;
//     expectedPower = context_.currentChannelsSettings().masterPower();
//     endTime       = currentTime + fastSunriseLength;
//     for (currentTime; currentTime < endTime; ++currentTime)
//     {
//         controller_.run(currentTime);
//         if ((currentTime - fastSunriseStartTime) % part == 0)
//         {
//             EXPECT_GE(context_.currentChannelsSettings().masterPower(), expectedPower - 2);
//             EXPECT_LE(context_.currentChannelsSettings().masterPower(), expectedPower + 2);
//             expectedPower += powerPart;
//         }
//     }

//     EXPECT_EQ(SunlightController::State::FastSunrise, controller_.state());
//     controller_.run(++currentTime);
//     EXPECT_EQ(SunlightController::State::Finished, controller_.state());

//     EXPECT_EQ(finalPower, context_.currentChannelsSettings().masterPower());
// }

TEST_F(SunlightControllerShould, PerformFastSunset)
{
    constexpr u8 initialPower = 90;
    constexpr u8 finalPower   = 10;

    constexpr u8 initialHour   = 0;
    constexpr u8 initialMinute = 0;
    constexpr u8 initialSecond = 12;

    constexpr std::time_t fastSunsetLength = 100;

    context_.currentChannelsSettings().masterPower(initialPower);
    context_.nightChannelsSettings().masterPower(finalPower);
    context_.fastSunsetLength(fastSunsetLength);

    std::time_t currentTime         = getTime(initialHour, initialMinute, initialSecond);
    std::time_t fastSunsetStartTime = currentTime;
    std::time_t endTime             = currentTime + fastSunsetLength;

    EXPECT_EQ(SunlightController::State::Finished, controller_.state());
    controller_.fastSunset(currentTime);

    EXPECT_EQ(SunlightController::State::FastSunset, controller_.state());

    int part          = fastSunsetLength / 10;
    int powerPart     = (initialPower - finalPower) / 10;
    int expectedPower = initialPower;
    for (currentTime; currentTime < endTime; ++currentTime)
    {
        controller_.run(currentTime);
        if ((currentTime - fastSunsetStartTime) % part == 0)
        {
            EXPECT_GE(context_.currentChannelsSettings().masterPower(), expectedPower - 2);
            EXPECT_LE(context_.currentChannelsSettings().masterPower(), expectedPower + 2);
            expectedPower -= powerPart;
        }
    }

    EXPECT_EQ(SunlightController::State::FastSunset, controller_.state());
    controller_.run(++currentTime);
    EXPECT_EQ(SunlightController::State::Finished, controller_.state());

    EXPECT_EQ(finalPower, context_.currentChannelsSettings().masterPower());
}

} // namespace controller
