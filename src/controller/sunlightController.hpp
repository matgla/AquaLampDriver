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
        FastCorrection,
        Finished
    };

    SunlightController(app::Context& context);


    State state() const;
    void fastSunrise(std::time_t startTime);
    void fastSunset(std::time_t startTime);
    void run(std::time_t currentTime);
    bool finished();

    void stop();

private:
    void updateState(std::time_t currentTime);
    void fastCorrection(std::time_t startTime, u8 setPointValue);

    std::time_t getSeconds(int hour, int minute, int second) const;
    std::time_t getSunriseStartTime() const;
    std::time_t getSunsetStartTime() const;

    std::time_t fastSunriseStartTime_;
    std::time_t fastSunsetStartTime_;
    std::time_t fastSunriseLength_;
    std::time_t fastSunsetLength_;

    std::time_t startTime_;
    u8 setPointValue_;

    logger::Logger logger_;

    State state_;

    app::Context& context_;
    float currentPower_;
};

} // namespace controller
