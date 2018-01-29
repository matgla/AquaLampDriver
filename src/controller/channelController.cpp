#include "controller/channelController.hpp"
#include "app/settings/lightChannel.hpp"

namespace controller
{

ChannelController::ChannelController()
    : startTime_(0), channel_(nullptr), logger_("ChannelController"), state_(State::Finished), operationState_(OperationState::Finished)
{
}

ChannelController::ChannelController(app::settings::LightChannel* channel)
    : startTime_(0), channel_(channel), logger_("ChannelController"), state_(State::Finished), operationState_(OperationState::Finished)
{
}

void ChannelController::run(std::time_t currentTime)
{
    updateState(currentTime);

    switch (state_)
    {
        case State::Finished:
        {
        }
        break;

        case State::Sunset:
        {
            update(channel_->getSunsetTime().length(), channel_->nightPower());
        }
        break;

        case State::Sunrise:
        {
            update(channel_->getSunriseTime().length(), channel_->dayPower());
        }
        break;

        case State::FastSunset:
        {
            update(channel_->fastOperationLength(), channel_->nightPower());
        }
        break;

        case State::FastSunrise:
        {
            update(channel_->fastOperationLength(), channel_->dayPower());
        }
        break;
        case State::FastCorrection:
        {
        }
        break;
    }

    step(currentTime);
}

void ChannelController::update(std::time_t length, u8 pointValue)
{
    length_     = length;
    pointValue_ = pointValue_;
}

void ChannelController::step(std::time_t currentTime)
{
    if (operationState_ == OperationState::Finished)
    {
        return;
    }
    const int timeToEnd = startTime_ + length_ - currentTime;
    if (timeToEnd <= 0)
    {
        int error = std::abs(pointValue_ - channel_->currentPower());
        if (error >= 5)
        {
            // TODO: remove hardcode for correction time
            logger_.info() << "Error to high, performing correction...";

            startTime_      = currentTime;
            length_         = 100;
            pointValue_     = pointValue_;
            operationState_ = OperationState::Correction;
            state_          = State::FastCorrection;
            return;
        }

        if (error < 5)
        {
            logger_.info() << "Corrected and finished";

            channel_->currentPower(pointValue_);
            operationState_ = OperationState::Finished;
            state_          = State::Finished;
            return;
        }

        logger_.info() << "Finished";
        operationState_ = OperationState::Finished;
        state_          = State::Finished;
    }

    if (operationState_ != OperationState::Correction)
    {
        operationState_ = OperationState::Ongoing;
    }
    const int leftPower = pointValue_ - channel_->currentPower();
    const float step    = static_cast<const float>(leftPower) / timeToEnd;
    logger_.info() << "Power left: " << leftPower;

    if (std::abs(currentPower_ - channel_->currentPower()) > 1)
    {
        currentPower_ = channel_->currentPower();
    }

    currentPower_ += step;
    const u8 newPower = static_cast<u8>(currentPower_);

    if (newPower != channel_->currentPower())
    {
        logger_.info() << "Set power to: " << newPower;

        channel_->currentPower(newPower);
    }
}

void ChannelController::setChannel(app::settings::LightChannel* channel)
{
    channel_ = channel;
}


std::time_t ChannelController::getSeconds(int hour, int minute, int second) const
{
    std::time_t currentTime = std::time(nullptr);
    std::tm* timeData       = localtime(&currentTime);
    timeData->tm_hour       = hour;
    timeData->tm_min        = minute;
    timeData->tm_sec        = second;

    return std::mktime(timeData);
}

std::time_t ChannelController::getSunriseStartTime() const
{
    return getSeconds(channel_->getSunriseTime().hour(),
                      channel_->getSunriseTime().minute(),
                      channel_->getSunriseTime().second());
}

std::time_t ChannelController::getSunsetStartTime() const
{
    return getSeconds(channel_->getSunsetTime().hour(),
                      channel_->getSunsetTime().minute(),
                      channel_->getSunsetTime().second());
}

void ChannelController::updateState(std::time_t currentTime)
{
    if (state_ == State::FastSunrise || state_ == State::FastSunset)
    {
        return;
    }
    const std::time_t sunsetStart = getSunsetStartTime();
    if (currentTime >= sunsetStart && currentTime < sunsetStart + channel_->getSunsetTime().length())
    {
        if (state_ != State::Sunset)
        {
            logger_.info() << "It's sunset time";
            std::time_t startTime = getSeconds(channel_->getSunsetTime().hour(),
                                               channel_->getSunsetTime().minute(),
                                               channel_->getSunsetTime().second());
            state_                = State::Sunset;
            operationState_       = OperationState::Ongoing;
            startTime_            = startTime;
            length_               = channel_->getSunsetTime().length();
            pointValue_           = channel_->nightPower();
        }

        return;
    }

    const std::time_t sunriseStart = getSunriseStartTime();

    logger_.info() << "currentTime: " << currentTime
                   << ", sunriseStart: " << sunriseStart
                   << ", sunriseLenght: " << channel_->getSunriseTime().length();

    if (currentTime >= sunriseStart && currentTime < sunriseStart + channel_->getSunriseTime().length())
    {
        if (state_ != State::Sunrise)
        {
            logger_.info() << "It's sunrise time";
            std::time_t startTime = getSeconds(channel_->getSunriseTime().hour(),
                                               channel_->getSunriseTime().minute(),
                                               channel_->getSunriseTime().second());
            state_                = State::Sunrise;
            operationState_       = OperationState::Ongoing;
            startTime_            = startTime;
            length_               = channel_->getSunriseTime().length();
            pointValue_           = channel_->dayPower();
        }
        return;
    }
}

void ChannelController::performFastSunrise(std::time_t startTime)
{
    logger_.info() << "Performing fast sunrise";
    state_          = State::FastSunrise;
    operationState_ = OperationState::Ongoing;
    startTime_      = startTime;
    length_         = channel_->fastOperationLength();
    pointValue_     = channel_->dayPower();
}

void ChannelController::performFastSunset(std::time_t startTime)
{
    logger_.info() << "Performing fast sunset";
    state_          = State::FastSunset;
    operationState_ = OperationState::Ongoing;
    startTime_      = startTime;
    length_         = channel_->fastOperationLength();
    pointValue_     = channel_->nightPower();
}

ChannelController::State ChannelController::state() const
{
    return state_;
}

} // namespace controller
