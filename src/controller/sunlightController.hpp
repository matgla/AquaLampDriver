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

    void stop();

private:
    std::time_t getSeconds(int hour, int minute, int second) const;
    std::time_t getSunriseStartTime() const;
    std::time_t getSunsetStartTime() const;

    std::time_t sunriseStartTime_;
    std::time_t sunsetStartTime_;

    std::time_t fastSunriseLength_;
    std::time_t fastSunsetLength_;

    logger::Logger logger_;

    State state_;

    app::Context& context_;
    float currentPower_;
};

} // namespace controller
