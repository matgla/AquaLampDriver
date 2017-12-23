#pragma once

#include <ctime>

#include "app/context.hpp"
#include "logger/logger.hpp"

namespace controller
{

class SunlightController
{
public:
    enum class State
    {
        Sunrise,
        Sunset,
        FastSunrise,
        FastSunset,
        Finished
    };

    SunlightController(app::Context& context);

    void updateState(std::time_t currentTime);

    State state() const;
    void run(std::time_t currentTime);
    bool finished();

    void setSunriseStartTime(const u8 hours, const u8 minutes, const u8 seconds);
    void setSunsetStartTime(const u8 hours, const u8 minutes, const u8 seconds);
    void setSunriseLength(const std::time_t sunriseLength);
    void setSunsetLength(const std::time_t sunsetLength);

    void stop();

private:
    std::time_t getSeconds(int hour, int minute, int second) const;
    std::time_t getSunriseStartTime() const;
    std::time_t getSunsetStartTime() const;

    u8 sunriseStartHour_;
    u8 sunriseStartMinute_;
    u8 sunriseStartSecond_;
    std::time_t sunriseLength_;
    std::time_t sunriseStartTime_;

    u8 sunsetStartHour_;
    u8 sunsetStartMinute_;
    u8 sunsetStartSecond_;
    std::time_t sunsetStartTime_;
    std::time_t sunsetLength_;

    logger::Logger logger_;

    State state_;

    app::Context& context_;
    float currentPower_;
};

} // namespace controller
