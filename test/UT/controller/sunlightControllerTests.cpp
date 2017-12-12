#include <gtest/gtest.h>

#include <chrono>
#include <ctime>

#include "controller/sunlightController.hpp"

#include <iostream>

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
protected:
    TimeStub time_;
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

TEST_F(SunlightControllerShould, StartInOffState)
{
    EXPECT_EQ(SunlightController::State::Off, controller_.state());
}

TEST_F(SunlightControllerShould, GoToSunriseOnTime)
{
    const std::time_t sunriseStart   = getTime(10, 10, 10);
    const std::time_t sunshineStart  = getTime(16, 0, 0);
    const std::time_t sunriseLength  = 3600; // seconds
    const std::time_t sunshineLength = 3600; // seconds

    controller_.setSunriseStartTime(sunriseStart);
    controller_.setSunriseLength(sunriseLength);
    TimeStub time(getTime(10, 10, 9));
    EXPECT_EQ(SunlightController::State::Off, controller_.state());
    controller_.run(time.getCurrentTime());
    EXPECT_EQ(SunlightController::State::Off, controller_.state());
    time.forwardTime(std::chrono::seconds(60));
    controller_.run(time.getCurrentTime());
    EXPECT_EQ(SunlightController::State::Sunrise, controller_.state());
}

} // namespace controller
