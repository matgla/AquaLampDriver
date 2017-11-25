#pragma once

#include <cstdio>

#include <boost/sml.hpp>

#include "app/context.hpp"
#include "app/statemachines/events.hpp"
#include "app/statemachines/states.hpp"

#define MAX_CHANNELS 13

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

        if (context.channelSetting.index == 0)
        {
            context.display.print(" Master: ");
            utils::writeToBufferAligned(buffer, context.channelSetting.masterPower, '\0', 3, ' ');
            context.display.print(buffer);
            context.display.print(" %");
        }
        else
        {
            context.display.print(" CH");
            utils::writeToBufferAligned(buffer, context.channelSetting.index, '\0', 2);
            context.display.print(buffer);
            context.display.print(": ");
            utils::writeToBufferAligned(buffer, context.channelSetting.power[context.channelSetting.index], '\0', 3, ' ');
            context.display.print(buffer);
            context.display.print(" %");
        }
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
        apply(context);
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
        apply(context);
    }

    static void apply(Context& context)
    {
        const auto& index = context.channelSetting.index;
        auto& board       = context.channelSetting.board_;
        switch (index)
        {
            case 0:
            {
                board.ledPwm1.setPulse(context.channelSetting.power[1] * (static_cast<float>(context.channelSetting.masterPower) / 100));
                board.ledPwm2.setPulse(context.channelSetting.power[2] * (static_cast<float>(context.channelSetting.masterPower) / 100));
                board.ledPwm3.setPulse(context.channelSetting.power[3] * (static_cast<float>(context.channelSetting.masterPower) / 100));
                board.ledPwm4.setPulse(context.channelSetting.power[4] * (static_cast<float>(context.channelSetting.masterPower) / 100));
                board.ledPwm5.setPulse(context.channelSetting.power[5] * (static_cast<float>(context.channelSetting.masterPower) / 100));
                board.ledPwm6.setPulse(context.channelSetting.power[6] * (static_cast<float>(context.channelSetting.masterPower) / 100));
                board.ledPwm7.setPulse(context.channelSetting.power[7] * (static_cast<float>(context.channelSetting.masterPower) / 100));
                board.ledPwm8.setPulse(context.channelSetting.power[8] * (static_cast<float>(context.channelSetting.masterPower) / 100));
                board.ledPwm9.setPulse(context.channelSetting.power[9] * (static_cast<float>(context.channelSetting.masterPower) / 100));
                board.ledPwm10.setPulse(context.channelSetting.power[10] * (static_cast<float>(context.channelSetting.masterPower) / 100));
                board.ledPwm11.setPulse(context.channelSetting.power[11] * (static_cast<float>(context.channelSetting.masterPower) / 100));
                board.ledPwm12.setPulse(context.channelSetting.power[12] * (static_cast<float>(context.channelSetting.masterPower) / 100));
                board.ledPwm13.setPulse(context.channelSetting.power[13] * (static_cast<float>(context.channelSetting.masterPower) / 100));
            }
            break;
            case 1:
            {
                board.ledPwm1.setPulse(context.channelSetting.power[index] * (static_cast<float>(context.channelSetting.masterPower) / 100));
            }
            break;
            case 2:
            {
                board.ledPwm2.setPulse(context.channelSetting.power[index] * (static_cast<float>(context.channelSetting.masterPower) / 100));
            }
            break;
            case 3:
            {
                board.ledPwm3.setPulse(context.channelSetting.power[index] * (static_cast<float>(context.channelSetting.masterPower) / 100));
            }
            break;
            case 4:
            {
                board.ledPwm4.setPulse(context.channelSetting.power[index] * (static_cast<float>(context.channelSetting.masterPower) / 100));
            }
            break;
            case 5:
            {
                board.ledPwm5.setPulse(context.channelSetting.power[index] * (static_cast<float>(context.channelSetting.masterPower) / 100));
            }
            break;
            case 6:
            {
                board.ledPwm6.setPulse(context.channelSetting.power[index] * (static_cast<float>(context.channelSetting.masterPower) / 100));
            }
            break;
            case 7:
            {
                board.ledPwm7.setPulse(context.channelSetting.power[index] * (static_cast<float>(context.channelSetting.masterPower) / 100));
            }
            break;
            case 8:
            {
                board.ledPwm8.setPulse(context.channelSetting.power[index] * (static_cast<float>(context.channelSetting.masterPower) / 100));
            }
            break;
            case 9:
            {
                board.ledPwm9.setPulse(context.channelSetting.power[index] * (static_cast<float>(context.channelSetting.masterPower) / 100));
            }
            break;
            case 10:
            {
                board.ledPwm10.setPulse(context.channelSetting.power[index] * (static_cast<float>(context.channelSetting.masterPower) / 100));
            }
            break;
            case 11:
            {
                board.ledPwm11.setPulse(context.channelSetting.power[index] * (static_cast<float>(context.channelSetting.masterPower) / 100));
            }
            break;
            case 12:
            {
                board.ledPwm12.setPulse(context.channelSetting.power[index] * (static_cast<float>(context.channelSetting.masterPower) / 100));
            }
            break;
            case 13:
            {
                board.ledPwm13.setPulse(context.channelSetting.power[index] * (static_cast<float>(context.channelSetting.masterPower) / 100));
            }
            break;
        }
    }
};

} // namespace statemachines
} // namepsace app