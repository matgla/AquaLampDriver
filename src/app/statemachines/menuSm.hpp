#pragma once

#include <cstdio>

#include <boost/sml.hpp>

#include "app/statemachines/channelSettingsSm.hpp"
#include "app/statemachines/events.hpp"
#include "app/statemachines/states.hpp"
#include "app/statemachines/timeSettingsSm.hpp"
#include "drivers/lcd/icons.hpp"

namespace app
{
namespace statemachines
{

struct MenuSm
{
    auto operator()() const noexcept
    {
        using namespace boost::sml;
        using namespace states;
        using namespace events;

        // clang-format off
            return make_transition_table(
                *state<ChannelSettings> + on_entry<_> / [](Context& context){DisplayMenu(context, 1);},
                state<TimeSettings> + on_entry<_> / [](Context& context){DisplayMenu(context, 2);},
                state<GeneralSettings> + on_entry<_> / [](Context& context){DisplayMenu(context, 3);},
                state<EffectSettings> + on_entry<_> / [](Context& context){DisplayMenu(context, 4);},
                
                state<About> + on_entry<_> / [](Context& context){DisplayMenu(context, 5);},
                state<ChannelSettings> + event<ButtonDown> = state<TimeSettings>,
                state<TimeSettings> + event<ButtonDown> = state<GeneralSettings>,
                state<GeneralSettings> + event<ButtonDown> = state<EffectSettings>,
                state<EffectSettings> + event<ButtonDown> = state<About>,
                state<About> + event<ButtonDown> = state<ChannelSettings>,
                state<ChannelSettings> + event<ButtonUp> = state<About>,
                state<TimeSettings> + event<ButtonUp> = state<ChannelSettings>,
                state<GeneralSettings> + event<ButtonUp> = state<TimeSettings>,
                state<EffectSettings> + event<ButtonUp> = state<GeneralSettings>,
                state<About> + event<ButtonUp> = state<EffectSettings>
                // state<ChannelSettings> + event<ButtonSelect> = state<ChannelSettingsSm>,
                // state<ChannelSettingsSm> + event<ButtonBack> = state<ChannelSettings>,
                // state<TimeSettings> + event<ButtonSelect> = state<TimeSettingsSm>,
                // state<TimeSettingsSm> + event<ButtonBack> = state<TimeSettings>
            );
        // clang-format on
    }

    static void DisplayMenu(Context& context, int selection)
    {
        using namespace drivers::lcd;
        auto& display = context.display;
        display.clear(Colors::OFF);
        display.print("     Menu\n");

        if (selection == 1)
        {
            display.drawImage(Images::fullTriangle);
            display.incrementCursorX(1);
            display.print("1.Channel\n");
            display.drawImage(Images::emptyTriangle);
            display.incrementCursorX(1);
            display.print("2.Time\n");
            display.drawImage(Images::emptyTriangle);
            display.incrementCursorX(1);
            display.print("3.General\n");
            display.drawImage(Images::emptyTriangle);
            display.incrementCursorX(1);
            display.print("4.Effects\n");
            display.drawImage(Images::emptyTriangle);
            display.incrementCursorX(1);
            display.print("5.About\n");
        }

        if (selection == 2)
        {
            display.drawImage(Images::emptyTriangle);
            display.incrementCursorX(1);
            display.print("1.Channel\n");
            display.drawImage(Images::fullTriangle);
            display.incrementCursorX(1);
            display.print("2.Time\n");
            display.drawImage(Images::emptyTriangle);
            display.incrementCursorX(1);
            display.print("3.General\n");
            display.drawImage(Images::emptyTriangle);
            display.incrementCursorX(1);
            display.print("4.Effects\n");
            display.drawImage(Images::emptyTriangle);
            display.incrementCursorX(1);
            display.print("5.About\n");
        }

        if (selection == 3)
        {
            display.drawImage(Images::emptyTriangle);
            display.incrementCursorX(1);
            display.print("1.Channel\n");
            display.drawImage(Images::emptyTriangle);
            display.incrementCursorX(1);
            display.print("2.Time\n");
            display.drawImage(Images::fullTriangle);
            display.incrementCursorX(1);
            display.print("3.General\n");
            display.drawImage(Images::emptyTriangle);
            display.incrementCursorX(1);
            display.print("4.Effects\n");
            display.drawImage(Images::emptyTriangle);
            display.incrementCursorX(1);
            display.print("5.About\n");
        }

        if (selection == 4)
        {
            display.drawImage(Images::emptyTriangle);
            display.incrementCursorX(1);
            display.print("1.Channel\n");
            display.drawImage(Images::emptyTriangle);
            display.incrementCursorX(1);
            display.print("2.Time\n");
            display.drawImage(Images::emptyTriangle);
            display.incrementCursorX(1);
            display.print("3.General\n");
            display.drawImage(Images::fullTriangle);
            display.incrementCursorX(1);
            display.print("4.Effects\n");
            display.drawImage(Images::emptyTriangle);
            display.incrementCursorX(1);
            display.print("5.About\n");
        }

        if (selection == 5)
        {
            display.drawImage(Images::emptyTriangle);
            display.incrementCursorX(1);
            display.print("1.Channel\n");
            display.drawImage(Images::emptyTriangle);
            display.incrementCursorX(1);
            display.print("2.Time\n");
            display.drawImage(Images::emptyTriangle);
            display.incrementCursorX(1);
            display.print("3.General\n");
            display.drawImage(Images::emptyTriangle);
            display.incrementCursorX(1);
            display.print("4.Effects\n");
            display.drawImage(Images::fullTriangle);
            display.incrementCursorX(1);
            display.print("5.About\n");
        }
    }
};

} // namespace statemachines
} // namepsace app
