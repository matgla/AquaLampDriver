#pragma once

#include <ctime>
#include <functional>

#include <boost/sml.hpp>

#include "app/context.hpp"
#include "app/statemachines/events.hpp"
#include "app/statemachines/states.hpp"
#include "display/display.hpp"
#include "display/images.hpp"
#include "hal/time/rtc.hpp"
#include "utils.hpp"


namespace app
{
namespace statemachines
{

namespace states
{
struct SetHours;
struct SetMinutes;
struct SetSeconds;
struct Saved;
} // namespace states

struct SetTimeSm
{
    auto operator()() const noexcept
    {
        using namespace boost::sml;
        using namespace states;
        using namespace events;

        // clang-format off
        // TODO: add posibility to go back wiht select from saved
        return make_transition_table(
            *state<Init> / onInit = state<SetHours>,
            state<SetHours> + on_entry<_> / onHours,
            state<SetMinutes> + on_entry<_> / onMinutes,
            state<SetSeconds> + on_entry<_> / onSeconds,

            state<SetHours> + event<ButtonSelect> / onSave = state<Saved>,
            state<SetMinutes> +event<ButtonSelect> / onSave = state<Saved>,
            state<SetSeconds> +event<ButtonSelect> / onSave = state<Saved>,

            state<Saved> + event<ButtonSelect> = X,
            state<Saved> +event<ButtonBack> = X,

            state<SetHours> + event<ButtonUp> / onHoursIncrement = state<SetHours>,
            state<SetHours> + event<ButtonDown> / onHoursDecrement = state<SetHours>,

            state<SetMinutes> +event<ButtonUp> / onMinutesIncrement = state<SetMinutes>,
            state<SetMinutes> +event<ButtonDown> / onMinutesDecrement = state<SetMinutes>,

            state<SetSeconds> +event<ButtonUp> / onSecondsIncrement = state<SetSeconds>,
            state<SetSeconds> +event<ButtonDown> / onSecondsDecrement = state<SetSeconds>,

            state<SetHours> + event<ButtonRight> = state<SetMinutes>,
            state<SetMinutes> +event<ButtonRight> = state<SetSeconds>,
            state<SetSeconds> +event<ButtonRight> = state<SetHours>,

            state<SetSeconds> +event<ButtonLeft> = state<SetMinutes>,
            state<SetMinutes> +event<ButtonLeft> = state<SetHours>,
            state<SetHours> +event<ButtonLeft> = state<SetSeconds>

        );
        // clang-format on
    }

    using Action = std::function<void(Context&)>;

    const Action onInit = [](Context& context) {
        switch (context.timeSettingOption)
        {
            case Context::TimeSettingOptions::SetSunshine:
            {
                // TODO: implement read from registers
            }
            break;
            case Context::TimeSettingOptions::SetSunrise:
            {
                // TODO: implement read from registers
            }
            break;
            case Context::TimeSettingOptions::SetTime:
            {
                std::time_t t          = std::time(nullptr);
                struct tm* currentTime = std::localtime(&t);
                auto& timeSetting      = context.timeSetting;
                timeSetting.hours      = currentTime->tm_hour;
                timeSetting.minutes    = currentTime->tm_min;
                timeSetting.seconds    = currentTime->tm_sec;
            }
            break;
        }

    };

    static TimeSetting* getTimeSettings(Context& context)
    {
        TimeSetting* settingsPtr = nullptr;
        if (Context::TimeSettingOptions::SetSunshine == context.timeSettingOption)
        {
            settingsPtr = &context.settings.sunshine;
        }
        else if (Context::TimeSettingOptions::SetSunrise == context.timeSettingOption)
        {
            settingsPtr = &context.settings.sunrise;
        }
        else if (Context::TimeSettingOptions::SetTime == context.timeSettingOption)
        {
            settingsPtr = &context.timeSetting;
        }

        HAL_ASSERT_MSG(settingsPtr != nullptr, "Wrong time setting option");
        return settingsPtr;
    }

    const Action onHoursIncrement = [](Context& context) {

        auto& hours = getTimeSettings(context)->hours;
        if (context.board_.upButton.isLongPressed())
        {
            hours += 5;
        }
        else
        {
            ++hours;
        }

        if (hours > 24)
        {
            hours = 24;
        }
    };


    const Action onHoursDecrement = [](Context& context) {
        auto& hours = getTimeSettings(context)->hours;

        if (context.board_.downButton.isLongPressed())
        {
            hours -= 5;
        }
        else
        {
            --hours;
        }

        if (hours < 0)
        {
            hours = 0;
        }
    };

    const Action onMinutesIncrement = [](Context& context) {
        auto& minutes = getTimeSettings(context)->minutes;

        if (context.board_.upButton.isLongPressed())
        {
            minutes += 5;
        }
        else
        {
            ++minutes;
        }

        if (minutes > 60)
        {
            minutes = 60;
        }
    };

    const Action onMinutesDecrement = [](Context& context) {
        auto& minutes = getTimeSettings(context)->minutes;

        if (context.board_.downButton.isLongPressed())
        {
            minutes -= 5;
        }
        else
        {
            --minutes;
        }

        if (minutes < 0)
        {
            minutes = 0;
        }
    };


    const Action onSecondsIncrement = [](Context& context) {
        auto& seconds = getTimeSettings(context)->seconds;

        if (context.board_.upButton.isLongPressed())
        {
            seconds += 5;
        }
        else
        {
            ++seconds;
        }

        if (seconds > 60)
        {
            seconds = 60;
        }
    };

    const Action onSecondsDecrement = [](Context& context) {
        auto& seconds = getTimeSettings(context)->seconds;

        if (context.board_.upButton.isLongPressed())
        {
            seconds -= 5;
        }
        else
        {
            --seconds;
        }

        if (seconds < 0)
        {
            seconds = 0;
        }
    };


    static void displayTime(Context& context, u8 arrowPosition)
    {
        auto& display = context.display;
        display.clear(display::Colors::OFF);
        if (Context::TimeSettingOptions::SetSunshine == context.timeSettingOption)
        {
            display.print("Set sunshine:\n\n");
        }
        else if (Context::TimeSettingOptions::SetSunrise == context.timeSettingOption)
        {
            display.print("Set sunrise:\n\n");
        }
        else if (Context::TimeSettingOptions::SetTime == context.timeSettingOption)
        {
            display.print("Set time:\n\n");
        }
        for (u8 i = 0; i < arrowPosition; ++i)
        {
            display.print(" ");
        }
        display.print("  ");

        display.drawImage(display::Images::ArrowDown);
        char buffer[50];

        std::tm time;

        switch (context.timeSettingOption)
        {
            case Context::TimeSettingOptions::SetSunshine:
            {
                time.tm_hour = context.settings.sunshine.hours;
                time.tm_min  = context.settings.sunshine.minutes;
                time.tm_sec  = context.settings.sunshine.seconds;
            }
            break;
            case Context::TimeSettingOptions::SetSunrise:
            {
                time.tm_hour = context.settings.sunrise.hours;
                time.tm_min  = context.settings.sunrise.minutes;
                time.tm_sec  = context.settings.sunrise.seconds;
            }
            break;
            case Context::TimeSettingOptions::SetTime:
            {
                time.tm_hour = context.timeSetting.hours;
                time.tm_min  = context.timeSetting.minutes;
                time.tm_sec  = context.timeSetting.seconds;
            }
            break;
        }


        utils::formatTime(buffer, 50, &time);

        display.print("\n   ");
        display.print(buffer);
        display.print("\n");
        for (u8 i = 0; i < arrowPosition; ++i)
        {
            display.print(" ");
        }
        display.print("  ");

        display.drawImage(display::Images::ArrowUp);

        context.display.setY(context.display.getWidth() - display::Images::backIcon.height);
        context.display.setX(2);
        context.display.drawImage(display::Images::backIcon);
        context.display.setX(context.display.getHeight() - display::Images::selectIcon.width - 2);
        context.display.drawImage(display::Images::selectIcon);
    }

    const Action onHours = [](Context& context) {
        displayTime(context, 2);
    };

    const Action onMinutes = [](Context& context) {
        displayTime(context, 5);
    };

    const Action onSeconds = [](Context& context) {
        displayTime(context, 8);
    };


    static void drawFrame(display::Display& display)
    {
        display.clear(display::Colors::OFF);

        for (int i = 0; i < 84; i += 2)
        {
            display.drawImage(display::Images::ChessboardMosaic);
        }
        display.setCursor(0, display::Images::ChessboardMosaic.height * 1 - 1);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.setCursor(84 - display::Images::ChessboardMosaic.width * 3, display::Images::ChessboardMosaic.height * 1 - 1);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.setCursor(0, display::Images::ChessboardMosaic.height * 2 - 2);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.setCursor(84 - display::Images::ChessboardMosaic.width * 3, display::Images::ChessboardMosaic.height * 2 - 2);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.setCursor(0, display::Images::ChessboardMosaic.height * 3 - 3);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.setCursor(84 - display::Images::ChessboardMosaic.width * 3, display::Images::ChessboardMosaic.height * 3 - 3);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.setCursor(0, display::Images::ChessboardMosaic.height * 4 - 4);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.setCursor(84 - display::Images::ChessboardMosaic.width * 3, display::Images::ChessboardMosaic.height * 4 - 4);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.setCursor(0, display::Images::ChessboardMosaic.height * 5 - 5);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.setCursor(84 - display::Images::ChessboardMosaic.width * 3, display::Images::ChessboardMosaic.height * 5 - 5);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.setCursor(0, display::Images::ChessboardMosaic.height * 6 - 6);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.setCursor(84 - display::Images::ChessboardMosaic.width * 3, display::Images::ChessboardMosaic.height * 6 - 6);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.drawImage(display::Images::ChessboardMosaic);
        display.setCursor(0, display::Images::ChessboardMosaic.height * 7 - 7);
        for (int i = 0; i < 84; i += 2)
        {
            display.drawImage(display::Images::ChessboardMosaic);
        }
    }

    const Action onSave = [](Context& context) {
        switch (context.timeSettingOption)
        {
            case Context::TimeSettingOptions::SetSunshine:
            {
                context.saveSettings();
            }
            break;
            case Context::TimeSettingOptions::SetSunrise:
            {
                context.saveSettings();
            }
            break;
            case Context::TimeSettingOptions::SetTime:
            {
                auto& t = context.timeSetting;
                hal::time::Rtc::get().setTime(t.hours, t.minutes, t.seconds);
            }
            break;
        }

        auto& display = context.display;
        drawFrame(context.display);
        const char* str = "Saved!";

        u8 cursorX = (display.getWidth() - strlen(str) * (display.getFont().width + 1)) / 2;
        u8 cursorY = (display.getHeight() - display.getFont().height) / 2;

        display.setCursor(cursorX,
                          cursorY);
        display.print(str);
    };
};

} // namespace statemachines
} // namespace app
