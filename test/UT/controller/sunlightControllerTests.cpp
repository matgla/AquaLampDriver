#include <gtest/gtest.h>

#include <chrono>
#include <ctime>

#include "controller/sunlightController.hpp"

class TimeStub
{
public:
    void incrementTime()
    {
        ++currentTime_;
    }

    template <typename T>
    void forwardTime(const T& duration)
    {
        currentTime_ += std::chrono::duration_cast<std::chrono::seconds>(duration).count();
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
    std::tm timeData;
    timeData.tm_hour = hour;
    timeData.tm_min  = minute;
    timeData.tm_sec  = second;

    return std::mktime(&timeData);
}

TEST_F(SunlightControllerShould, StartInOffState)
{
    EXPECT_EQ(SunlightController::State::Off, controller_.state());
}

} // namespace controller
