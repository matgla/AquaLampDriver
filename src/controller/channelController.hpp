#pragma once

#include <ctime>
#include <functional>

#include "logger/logger.hpp"
#include "utils/types.hpp"

namespace controller
{

class ChannelController
{
public:
    enum class State
    {
        Finished,
        Correction,
        Ongoing
    };
    ChannelController(u8& channelPower);
    void start(std::time_t startTime, std::time_t length, u8 pointValue);
    State run(std::time_t time);
    void reset(std::time_t startTime, std::time_t length, u8 pointValue);
    void update(std::time_t length, u8 pointValue);

private:
    std::time_t startTime_;
    std::time_t length_;
    u8 pointValue_;
    u8& channelPower_;

    float currentPower_;
    logger::Logger logger_;
    State state_;
};

} // namespace controller
