#pragma once

#include <ctime>
#include <functional>

#include "logger/logger.hpp"
#include "utils/types.hpp"

namespace app
{
namespace settings
{
class LightChannel;
} // namespace settings
} // namespace app

namespace controller
{

class ChannelController
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

    enum class OperationState
    {
        Finished,
        Correction,
        Ongoing
    };

    ChannelController();
    ChannelController(app::settings::LightChannel* channel);
    void setChannel(app::settings::LightChannel* channel);
    void start(std::time_t startTime, std::time_t length, u8 pointValue);
    void step(std::time_t time);
    void run(std::time_t time);
    void reset(std::time_t startTime, std::time_t length, u8 pointValue);
    void update(std::time_t length, u8 pointValue);
    void performFastSunrise(std::time_t startTime);
    void performFastSunset(std::time_t startTime);
    State state() const;

private:
    void updateState(std::time_t currentTime);
    std::time_t getSunriseStartTime() const;
    std::time_t getSunsetStartTime() const;
    std::time_t getSeconds(int hour, int minute, int second) const;

    std::time_t startTime_;
    app::settings::LightChannel* channel_;

    float currentPower_;
    logger::Logger logger_;
    State state_;
    OperationState operationState_;

    u8 pointValue_;
    std::time_t length_;
};

} // namespace controller
