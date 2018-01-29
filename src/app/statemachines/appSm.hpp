#pragma once

#include <cstdio>
#include <ctime>
#include <functional>

#include <boost/sml.hpp>

#include "app/contextInterface.hpp"
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
            *state<Init> / [](ContextInterface<auto>& context){init(context);} = state<DisplayInfo>,
            state<DisplayInfo> + event<ButtonDown> = state<MenuSm>,
            state<DisplayInfo> + event<ButtonLeft> / [](ContextInterface<auto>& context){DecrementBrightness(context);} = state<DisplayInfo>,
            state<DisplayInfo> + event<ButtonRight> / [](ContextInterface<auto>& context){IncrementBrightness(context);} = state<DisplayInfo>,
            state<DisplayInfo> + event<ButtonUp> = state<MenuSm>,
            state<DisplayInfo> + event<ButtonSelect> = state<MenuSm>,
            state<DisplayInfo> + event<ButtonBack> / [](ContextInterface<auto>& context){
                // context.forcedLight = false;
            } = state<DisplayInfo>,
            state<DisplayInfo> + event<Update> / 
            [](ContextInterface<auto>& context)
            {
                DisplayTime(context); 
                
            } = state<DisplayInfo>,           
            state<MenuSm> + event<ButtonBack> / [](ContextInterface<auto>& context){DisplayTime(context);} = state<DisplayInfo>
        );
        // clang-format on
    }

    static void init(ContextInterface<auto>& context)
    {
        DisplayTime(context);
    }

    static void DisplayTime(ContextInterface<auto>& context)
    {
        // context.display.clear(display::Colors::OFF);
        // constexpr const int TimeBufferSize = 9;
        // constexpr const int DateBufferSize = 12;
        // char timeBuffer[TimeBufferSize];
        // char dateBuffer[DateBufferSize];
        // auto t                 = std::time(nullptr);
        // struct tm* currentTime = std::localtime(&t);
        // utils::formatDate(dateBuffer, DateBufferSize, currentTime);
        // utils::formatTime(timeBuffer, TimeBufferSize, currentTime);
        // context.display.print("");
        // context.display.print(dateBuffer);
        // if (context.forcedLight)
        // {
        //     context.display.print("  F");
        // }
        // context.display.print("\n");
        // context.display.print(timeBuffer);
        // context.display.print("\nPower: ");
        // char buffer[5];
        // utils::writeToBufferAligned(buffer, context.masterPower, '\0', 3, ' ');
        // context.display.print(buffer);
        // context.display.print(" %\nTL: ");
        // float temp = context.temperatures_[0];
        // auto conv  = utils::floatToInts(temp, 1);
        // utils::itoa(conv.first, buffer);
        // context.display.print(buffer);
        // context.display.print(".");
        // utils::itoa(conv.second, buffer);
        // context.display.print(buffer);
        // temp = context.temperatures_[1];
        // context.display.print("  TR: ");
        // conv = utils::floatToInts(temp, 1);
        // utils::itoa(conv.first, buffer);
        // context.display.print(buffer);
        // context.display.print(".");
        // utils::itoa(conv.second, buffer);
        // context.display.print(buffer);
    }

    // static void delayedSave(Context& context)
    // {
    //     if (context.changedPower)
    //     {
    //         auto* timer = context.timerManager.getTimeoutTimer(context.saveTimer);
    //         if (timer)
    //         {
    //             timer->restart(5000);
    //         }
    //     }
    //     else
    //     {
    //         context.saveTimer    = context.timerManager.setTimeout(5000, [&context] {
    //             context.settings = context.temporarySettings;
    //             context.saveSettings();
    //             context.changedPower = false;
    //         });
    //         context.changedPower = true;
    //     }
    // }

    static void IncrementBrightness(Context& context)
    {
        // context.forcedLight = true;

        // if (context.board_.rightButton.isLongPressed())
        // {
        //     context.masterPower += 5;
        // }
        // else
        // {
        //     ++context.masterPower;
        // }

        // if (context.masterPower > 100)
        // {
        //     context.masterPower = 100;
        // }
        // ApplyBrightness(context);
    }

    static void DecrementBrightness(Context& context)
    {
        // context.forcedLight = true;

        // if (context.board_.leftButton.isLongPressed())
        // {
        //     context.masterPower -= 5;
        // }
        // else
        // {
        //     --context.masterPower;
        // }

        // if (context.masterPower > 101)
        // {
        //     context.masterPower = 0;
        // }

        // ApplyBrightness(context);
    }

    static void ApplyBrightness(Context& context)
    {
        // auto& board = context.board_;

        // board.ledPwm1.setPulse(context.temporarySettings.channelPowers[1] * (static_cast<float>(context.masterPower) / 100));
        // board.ledPwm2.setPulse(context.temporarySettings.channelPowers[2] * (static_cast<float>(context.masterPower) / 100));
        // board.ledPwm3.setPulse(context.temporarySettings.channelPowers[3] * (static_cast<float>(context.masterPower) / 100));
        // board.ledPwm4.setPulse(context.temporarySettings.channelPowers[4] * (static_cast<float>(context.masterPower) / 100));
        // board.ledPwm5.setPulse(context.temporarySettings.channelPowers[5] * (static_cast<float>(context.masterPower) / 100));
        // board.ledPwm6.setPulse(context.temporarySettings.channelPowers[6] * (static_cast<float>(context.masterPower) / 100));
        // board.ledPwm7.setPulse(context.temporarySettings.channelPowers[7] * (static_cast<float>(context.masterPower) / 100));
        // board.ledPwm8.setPulse(context.temporarySettings.channelPowers[8] * (static_cast<float>(context.masterPower) / 100));
        // board.ledPwm9.setPulse(context.temporarySettings.channelPowers[9] * (static_cast<float>(context.masterPower) / 100));
        // board.ledPwm10.setPulse(context.temporarySettings.channelPowers[10] * (static_cast<float>(context.masterPower) / 100));
        // board.ledPwm11.setPulse(context.temporarySettings.channelPowers[11] * (static_cast<float>(context.masterPower) / 100));
        // board.ledPwm12.setPulse(context.temporarySettings.channelPowers[12] * (static_cast<float>(context.masterPower) / 100));
        // board.ledPwm13.setPulse(context.temporarySettings.channelPowers[13] * (static_cast<float>(context.masterPower) / 100));
        // hal::core::startCriticalSection();
        // DisplayTime(context);
        // hal::core::stopCriticalSection();
    }
};

} // namespace statemachines
} // namepsace app