#pragma once

#include <cstdio>

#include <boost/sml.hpp>

#include "app/context.hpp"
#include "app/statemachines/events.hpp"
#include "app/statemachines/states.hpp"

#define MAX_CHANNELS 12

namespace app
{
namespace statemachines
{

struct ChannelSettingsSm
{
    auto operator()() const noexcept
    {
        using namespace boost::sml;
        using namespace states;
        using namespace events;
        // clang-format off
        return make_transition_table(
            *state<Init> / [](Context& context){ context.display.clear(display::Colors::OFF); }  = state<ChannelSettings>,
            state<ChannelSettings> + on_entry<_> / [](Context& context) { onShow(context); },
            state<ChannelSettings> + event<ButtonDown> / [](Context& context) { onIncrementChannel(context); } = state<ChannelSettings>,
            state<ChannelSettings> + event<ButtonUp> / [](Context& context) { onDecrementChannel(context); } = state<ChannelSettings>,
            state<ChannelSettings> + event<ButtonLeft> / [](Context& context) { onDecrementPower(context); } = state<ChannelSettings>,
            state<ChannelSettings> + event<ButtonRight> / [](Context& context) { onIncrementPower(context); } = state<ChannelSettings>
        );
        // clang-format on
    }

    static void onShow(Context& context)
    {
        using namespace drivers::lcd;
        context.display.clear(display::Colors::OFF);
        context.display.print("Channel conf:\n\n\n");
        char buffer[5];

        // sprintf(buffer, " CH%d: %3d%%\n", context.channelSetting.index, context.channelSetting.power[context.channelSetting.index]);
        context.display.print(" CH");
        utils::writeToBufferAligned(buffer, context.channelSetting.index, '\0', 2);

        context.display.print(buffer);
        context.display.print(": ");
        utils::writeToBufferAligned(buffer, context.channelSetting.power[context.channelSetting.index], '\0', 3, ' ');
        context.display.print(buffer);
        context.display.print(" %");

        context.display.setY(48 - display::Images::backIcon.height);
        context.display.setX(2);
        context.display.drawImage(display::Images::backIcon);
        context.display.setX(84 - display::Images::selectIcon.width - 2);
        context.display.drawImage(display::Images::selectIcon);
    }

    static void onIncrementChannel(Context& context)
    {
        if (context.channelSetting.index < MAX_CHANNELS)
        {
            ++context.channelSetting.index;
        }
        else
        {
            context.channelSetting.index = 0;
        }
    }

    static void onDecrementChannel(Context& context)
    {
        if (context.channelSetting.index > 0)
        {
            --context.channelSetting.index;
        }
        else
        {
            context.channelSetting.index = MAX_CHANNELS;
        }
    }

    static void onIncrementPower(Context& context)
    {
        if (context.channelSetting.board_.rightButton.isLongPressed())
        {
            context.channelSetting.power[context.channelSetting.index] += 5;
        }
        else
        {
            ++context.channelSetting.power[context.channelSetting.index];
        }

        if (context.channelSetting.power[context.channelSetting.index] > 100)
        {
            context.channelSetting.power[context.channelSetting.index] = 100;
        }
    }

    static void onDecrementPower(Context& context)
    {
        if (context.channelSetting.board_.leftButton.isLongPressed())
        {
            context.channelSetting.power[context.channelSetting.index] -= 5;
        }
        else
        {
            --context.channelSetting.power[context.channelSetting.index];
        }

        if (context.channelSetting.power[context.channelSetting.index] > 101)
        {
            context.channelSetting.power[context.channelSetting.index] = 0;
        }
    }
};

} // namespace statemachines
} // namepsace app