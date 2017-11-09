#pragma once

#include <boost/sml.hpp>

#include "app/context.hpp"
#include "app/statemachines/events.hpp"
#include "app/statemachines/setSunriseSm.hpp"
#include "app/statemachines/setSunshineSm.hpp"
#include "app/statemachines/setTimeSm.hpp"
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
            state<TimeSettings> + event<ButtonSelect> / [](Context& context) { onSetTime(context); } = state<SetTimeSm>,
            state<SetTimeSm> + event<ButtonBack> / [](Context& context) { onDrawMenu(context, 1); } = state<TimeSettings>,
            state<SunshineSettings> + event<ButtonSelect> / [](Context& context) { onSetSunshine(context); } = state<SetTimeSm>,
            state<SetTimeSm> + event<ButtonBack> / [](Context& context) { onDrawMenu(context, 1); } = state<SunshineSettings>,
            state<SunriseSettings> + event<ButtonSelect> / [](Context& context) { onSetSunrise(context); } = state<SetTimeSm>,
            state<SetTimeSm> + event<ButtonBack> / [](Context& context) { onDrawMenu(context, 1); } = state<SunriseSettings>
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

    static void onSetTime(Context& context)
    {
        context.timeSettingOption = Context::TimeSettingOptions::SetTime;
    }
    
    static void onSetSunshine(Context& context)
    {
        context.timeSettingOption = Context::TimeSettingOptions::SetSunshine;
    }
    
    static void onSetSunrise(Context& context)
    {
        context.timeSettingOption = Context::TimeSettingOptions::SetSunrise;
    }
};

} // namespace statemachines
} // namespace app
