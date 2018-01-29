#pragma once

#include <gsl/span>

#include "app/settings/lightChannel.hpp"

namespace app
{

template <typename ContextImpl>
class ContextInterface
{
public:
    void read()
    {
        return static_cast<ContextImpl*>(this)->readImpl();
    }

    void store()
    {
        return static_cast<ContextImpl*>(this)->storeImpl();
    }

    void init()
    {
        return static_cast<ContextImpl*>(this)->initImpl();
    }

    gsl::span<settings::LightChannel> getAllChannels()
    {
        return static_cast<ContextImpl*>(this)->getAllChannelsImpl();
    }

    gsl::span<const settings::LightChannel> getAllChannels() const
    {
        return static_cast<const ContextImpl*>(this)->getAllChannelsImpl();
    }

    const settings::LightChannel& masterChannel() const
    {
        return static_cast<const ContextImpl*>(this)->masterChannelImpl();
    }

    settings::LightChannel& masterChannel()
    {
        return static_cast<ContextImpl*>(this)->masterChannelImpl();
    }
};


} // namespace span
