#pragma once

#include <ctime>

#include "logger/logger.hpp"

namespace controller
{

class SunlightController
{
public:
    enum class State
    {
        Off,
        Sunrise,
        Sunshine
    };

    SunlightController();
    SunlightController(const std::time_t sunriseStartTime,
                       const std::time_t sunriseLength,
                       const std::time_t sunshineStartTime,
                       const std::time_t sunshineLength);

    const State state() const;
    void run(std::time_t currentTime);

    void setSunriseStartTime(const std::time_t sunriseStartTime);
    void setSunshineStartTime(const std::time_t sunshineStartTime);
    void setSunriseLength(const std::time_t sunriseLength);
    void setSunshineLength(const std::time_t sunshineLength);

private:
    std::time_t sunriseStartTime_;
    std::time_t sunshineStartTime_;
    std::time_t sunriseLength_;
    std::time_t sunshineLength_;

    logger::Logger logger_;

    State state_;
};

} // namespace controller
