#pragma once

#include <cstdio>

#include <boost/sml.hpp>

#include "app/context.hpp"
#include "app/statemachines/events.hpp"
#include "app/statemachines/states.hpp"
#include "drivers/lcd/icons.hpp"

namespace app
{
namespace statemachines
{

namespace states
{
struct SunriseSettings;
struct SunshineSettings;
struct DateSettings;
struct SetDate;
struct SetSunrise;
struct SetSunshine;
struct SetTime;

struct SetHourFirst;
struct SetHourSecond;
struct SetMinuteFirst;
struct SetMinuteSecond;
struct SetSecondFirst;
struct SetSecondSecond;
} // namespace states

struct TimeSettingsSm
{
    auto operator()() const noexcept
    {
        using namespace boost::sml;
        using namespace states;
        using namespace events;
        // clang-format off
        return make_transition_table(
            *state<Init> / [](Context& context){ onDrawMenu(context, 1); } = state<TimeSettings>,
            state<TimeSettings> + event<ButtonDown> / [](Context& context) { onDrawMenu(context, 2); } = state<DateSettings>,
            state<DateSettings> + event<ButtonDown> / [](Context& context) { onDrawMenu(context, 3); } = state<SunriseSettings>,
            state<SunriseSettings> + event<ButtonDown> / [](Context& context) { onDrawMenu(context, 4); } = state<SunshineSettings>,
            state<SunshineSettings> + event<ButtonDown> / [](Context& context) { onDrawMenu(context, 1); } = state<TimeSettings>,
            state<TimeSettings> + event<ButtonUp> / [](Context& context) { onDrawMenu(context, 4); } = state<SunshineSettings>,
            state<DateSettings> + event<ButtonUp> / [](Context& context) { onDrawMenu(context, 1); } = state<TimeSettings>,
            state<SunriseSettings> + event<ButtonUp> / [](Context& context) { onDrawMenu(context, 2); } = state<DateSettings>,
            state<SunshineSettings> + event<ButtonUp> / [](Context& context) { onDrawMenu(context, 3); } = state<SunriseSettings>,
            state<TimeSettings> + event<ButtonSelect> / [](Context& context) { onSetTime(context); } = state<SetTime>,
            state<SetTime> + event<ButtonBack> / [](Context& context) { onDrawMenu(context, 1); } = state<TimeSettings>,
            state<SetTime> = state<SetHourFirst>,
            state<SetHourFirst> + on_entry<_>

        );
        // clang-format on
    }

    static void onDrawMenu(Context& context, u8 selectedPosition)
    {
        using namespace drivers::lcd;
        auto& display = context.display;
        display.clear(drivers::lcd::Colors::OFF);
        display.print("Time:\n");

        if (1 == selectedPosition)
        {
            display.drawImage(Images::fullTriangle);
        }
        else
        {
            display.drawImage(Images::emptyTriangle);
        }
        display.print("Set time\n");
        if (2 == selectedPosition)
        {
            display.drawImage(Images::fullTriangle);
        }
        else
        {
            display.drawImage(Images::emptyTriangle);
        }
        display.print("Set date\n");
        if (3 == selectedPosition)
        {
            display.drawImage(Images::fullTriangle);
        }
        else
        {
            display.drawImage(Images::emptyTriangle);
        }
        display.print("Set sunshine\n");
        if (4 == selectedPosition)
        {
            display.drawImage(Images::fullTriangle);
        }
        else
        {
            display.drawImage(Images::emptyTriangle);
        }
        display.print("Set sunrise\n");
    }

    static void onSetTime(Context& context, u8 arrowPosition)
    {
        using namespace drivers::lcd;
        auto& display = context.display;
        display.clear(Colors::OFF);
        display.print("Set time:\n");

        for (u8 i = 0; i < arrowPosition; ++i)
        {
            display.print(" ");
        }
        display.drawImage(Images::ArrowDown);

        char buffer[50];
        sprintf(buffer, "\n %2d:%2d:%2d \n", context.timeSetting.hours, context.timeSetting.minutes, context.timeSetting.seconds);
        display.print(buffer);

        for (u8 i = 0; i < arrowPosition; ++i)
        {
            display.print(" ");
        }

        display.drawImage(Images::ArrowUp);
    }
};

} // namespace statemachines
} // namepsace app
