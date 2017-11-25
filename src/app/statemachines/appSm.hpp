#pragma once

#include <cstdio>
#include <ctime>
#include <functional>

#include <boost/sml.hpp>

#include "app/context.hpp"
#include "app/statemachines/events.hpp"
#include "app/statemachines/helpers.hpp"
#include "app/statemachines/menuSm.hpp"
#include "app/statemachines/states.hpp"
#include "hal/core/criticalSection.hpp"
#include "utils.hpp"

namespace app
{
namespace statemachines
{

struct AppSm
{
    auto operator()() const noexcept
    {
        using namespace boost::sml;
        using namespace states;
        using namespace events;
        // clang-format off
        return make_transition_table(
            *state<Init> / [](Context& context){DisplayTime(context);} = state<DisplayInfo>,
            state<DisplayInfo> + event<ButtonDown> = state<MenuSm>,
            state<DisplayInfo> + event<ButtonLeft> / [](Context& context){DecrementBrightness(context);} = state<DisplayInfo>,
            state<DisplayInfo> + event<ButtonRight> / [](Context& context){IncrementBrightness(context);} = state<DisplayInfo>,
            state<DisplayInfo> + event<ButtonUp> = state<MenuSm>,
            state<DisplayInfo> + event<ButtonSelect> = state<MenuSm>,
            state<DisplayInfo> + event<Update> / [](Context& context){DisplayTime(context);} = state<DisplayInfo>,           
            state<MenuSm> + event<ButtonBack> / [](Context& context){DisplayTime(context);} = state<DisplayInfo>
        );
        // clang-format on
    }

    static void DisplayTime(Context& context)
    {
        context.display.clear(display::Colors::OFF);
        constexpr const int TimeBufferSize = 9;
        constexpr const int DateBufferSize = 12;
        char timeBuffer[TimeBufferSize];
        char dateBuffer[DateBufferSize];
        auto t                 = std::time(nullptr);
        struct tm* currentTime = std::localtime(&t);
        utils::formatDate(dateBuffer, DateBufferSize, currentTime);
        utils::formatTime(timeBuffer, TimeBufferSize, currentTime);
        context.display.print("");
        context.display.print(dateBuffer);
        context.display.print("\n");
        context.display.print(timeBuffer);
        context.display.print("\nPower: ");
        char buffer[5];
        utils::writeToBufferAligned(buffer, context.channelSetting.masterPower, '\0', 3, ' ');
        context.display.print(buffer);
        context.display.print(" %\nTL: ");
        float temp = context.temperatures_[0];
        auto conv  = utils::floatToInts(temp, 1);
        utils::itoa(conv.first, buffer);
        context.display.print(buffer);
        context.display.print(".");
        utils::itoa(conv.second, buffer);
        context.display.print(buffer);
        temp = context.temperatures_[1];
        context.display.print("  TR: ");
        conv = utils::floatToInts(temp, 1);
        utils::itoa(conv.first, buffer);
        context.display.print(buffer);
        context.display.print(".");
        utils::itoa(conv.second, buffer);
        context.display.print(buffer);
    }

    static void IncrementBrightness(Context& context)
    {
        if (context.channelSetting.board_.rightButton.isLongPressed())
        {
            context.channelSetting.masterPower += 5;
        }
        else
        {
            ++context.channelSetting.masterPower;
        }

        if (context.channelSetting.masterPower > 100)
        {
            context.channelSetting.masterPower = 100;
        }
        ApplyBrightness(context);
    }

    static void DecrementBrightness(Context& context)
    {
        if (context.channelSetting.board_.leftButton.isLongPressed())
        {
            context.channelSetting.masterPower -= 5;
        }
        else
        {
            --context.channelSetting.masterPower;
        }

        if (context.channelSetting.masterPower > 101)
        {
            context.channelSetting.masterPower = 0;
        }
        ApplyBrightness(context);
    }

    static void ApplyBrightness(Context& context)
    {
        auto& board = context.channelSetting.board_;

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
        hal::core::startCriticalSection();
        DisplayTime(context);
        hal::core::stopCriticalSection();
    }
};

} // namespace statemachines
} // namepsace app