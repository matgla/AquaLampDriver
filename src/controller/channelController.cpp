#include "controller/channelController.hpp"

namespace controller
{

ChannelController::ChannelController(u8& channelPower)
    : startTime_(0), length_(0), pointValue_(0), channelPower_(channelPower), logger_("ChannelController"), state_(State::Finished)
{
}

void ChannelController::start(std::time_t startTime, std::time_t length, u8 pointValue)
{
    logger_.info() << "Starting with data { startTime:" << startTime
                   << ", length: " << length << ", pointValue: " << pointValue
                   << ", channelPower: " << channelPower_;
    startTime_    = startTime;
    length_       = length;
    pointValue_   = pointValue;
    currentPower_ = channelPower_;
    state_        = State::Ongoing;
}

ChannelController::State ChannelController::run(std::time_t currentTime)
{
    if (state_ == State::Finished)
    {
        return state_;
    }
    const int timeToEnd = startTime_ + length_ - currentTime;
    if (timeToEnd <= 0)
    {
        int error = std::abs(pointValue_ - channelPower_);
        if (error >= 5)
        {
            // TODO: remove hardcode for correction time
            logger_.info() << "Error to high, performing correction...";

            reset(currentTime, 100, pointValue_);
            state_ = State::Correction;
            return state_;
        }

        if (error < 5)
        {
            logger_.info() << "Corrected and finished";

            channelPower_ = pointValue_;
            state_        = State::Finished;
            return state_;
        }

        logger_.info() << "Finished";
        state_ = State::Finished;
        return state_;
    }

    if (state_ != State::Correction)
    {
        state_ = State::Ongoing;
    }
    const int leftPower = pointValue_ - channelPower_;
    const float step    = static_cast<const float>(leftPower) / timeToEnd;
    logger_.info() << "Power left: " << leftPower;

    if (std::abs(currentPower_ - channelPower_) > 1)
    {
        currentPower_ = channelPower_;
    }

    currentPower_ += step;
    const u8 newPower = static_cast<u8>(currentPower_);

    if (newPower != channelPower_)
    {
        logger_.info() << "Set power to: " << newPower;

        channelPower_ = newPower;
    }
    return state_;
}

void ChannelController::reset(std::time_t startTime, std::time_t length, u8 pointValue)
{
    startTime_  = startTime;
    length_     = length;
    pointValue_ = pointValue;
}

void ChannelController::update(std::time_t length, u8 pointValue)
{
    length_     = length;
    pointValue_ = pointValue;
}


} // namespace controller
