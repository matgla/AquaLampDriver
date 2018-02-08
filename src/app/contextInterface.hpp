#pragma once

#include <gsl/span>

#include "app/settings/lightChannel.hpp"

namespace app
{

class IContext
{
public:
    virtual void load()                                                    = 0;
    virtual void store()                                                   = 0;
    virtual gsl::span<settings::LightChannel> getAllChannels()             = 0;
    virtual gsl::span<const settings::LightChannel> getAllChannels() const = 0;
    virtual const settings::LightChannel& masterChannel() const            = 0;
    virtual settings::LightChannel& masterChannel()                        = 0;
};

} // namespace span
