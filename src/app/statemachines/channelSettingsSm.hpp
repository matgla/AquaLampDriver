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
            *state<Init> / [](Context& context){ context.display.clear(display::Colors::OFF); context.temporarySettings = context.settings;}  = state<ChannelSettings>,
            state<ChannelSettings> + on_entry<_> / [](Context& context) { onShow(context); },
            state<ChannelSettings> + event<ButtonDown> / [](Context& context) { onIncrementChannel(context); } = state<ChannelSettings>,
            state<ChannelSettings> + event<ButtonUp> / [](Context& context) { onDecrementChannel(context); } = state<ChannelSettings>,
            state<ChannelSettings> + event<ButtonLeft> / [](Context& context) { onDecrementPower(context); } = state<ChannelSettings>,
            state<ChannelSettings> + event<ButtonRight> / [](Context& context) { onIncrementPower(context); } = state<ChannelSettings>,
            state<ChannelSettings> + event<ButtonSelect> / onSave = state<Saved>,
            state<Saved> + on_entry<_> / [](Context& context) { drawSave(context); },
            state<Saved> + event<ButtonSelect> = state<ChannelSettings>
        );
        // clang-format on
    }

    static void onShow(Context& context)
    {
        using namespace drivers::lcd;
        context.display.clear(display::Colors::OFF);
        context.display.print("Channel conf:\n\n\n");
        char buffer[5];

        if (context.temporarySettings.channelIndex == 0)
        {
            context.display.print(" Master: ");
            utils::writeToBufferAligned(buffer, context.temporarySettings.channelPowers[0], '\0', 3, ' ');
            context.display.print(buffer);
            context.display.print(" %");
        }
        else
        {
            context.display.print(" CH");
            utils::writeToBufferAligned(buffer, context.temporarySettings.channelIndex, '\0', 2);
            context.display.print(buffer);
            context.display.print(": ");
            utils::writeToBufferAligned(buffer, context.temporarySettings.channelPowers[context.temporarySettings.channelIndex], '\0', 3, ' ');
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
        if (context.temporarySettings.channelIndex < MAX_CHANNELS)
        {
            ++context.temporarySettings.channelIndex;
        }
        else
        {
            context.temporarySettings.channelIndex = 0;
        }
    }

    static void onDecrementChannel(Context& context)
    {
        if (context.temporarySettings.channelIndex > 0)
        {
            --context.temporarySettings.channelIndex;
        }
        else
        {
            context.temporarySettings.channelIndex = MAX_CHANNELS;
        }
    }

    static void onIncrementPower(Context& context)
    {
        if (context.board_.rightButton.isLongPressed())
        {
            context.temporarySettings.channelPowers[context.temporarySettings.channelIndex] += 5;
        }
        else
        {
            ++context.temporarySettings.channelPowers[context.temporarySettings.channelIndex];
        }

        if (context.temporarySettings.channelPowers[context.temporarySettings.channelIndex] > 100)
        {
            context.temporarySettings.channelPowers[context.temporarySettings.channelIndex] = 100;
        }
    }

    static void onDecrementPower(Context& context)
    {
        if (context.board_.leftButton.isLongPressed())
        {
            context.temporarySettings.channelPowers[context.temporarySettings.channelIndex] -= 5;
        }
        else
        {
            --context.temporarySettings.channelPowers[context.temporarySettings.channelIndex];
        }

        if (context.temporarySettings.channelPowers[context.temporarySettings.channelIndex] > 101)
        {
            context.temporarySettings.channelPowers[context.temporarySettings.channelIndex] = 0;
        }
    }

    using Action = std::function<void(Context&)>;

    static void apply(Context& context)
    {
        context.settings  = context.temporarySettings;
        const auto& index = context.temporarySettings.channelIndex;
        auto& board       = context.board_;
        switch (index)
        {
            case 0:
            {
                board.ledPwm1.setPulse(context.settings.channelPowers[1] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
                board.ledPwm2.setPulse(context.settings.channelPowers[2] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
                board.ledPwm3.setPulse(context.settings.channelPowers[3] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
                board.ledPwm4.setPulse(context.settings.channelPowers[4] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
                board.ledPwm5.setPulse(context.settings.channelPowers[5] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
                board.ledPwm6.setPulse(context.settings.channelPowers[6] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
                board.ledPwm7.setPulse(context.settings.channelPowers[7] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
                board.ledPwm8.setPulse(context.settings.channelPowers[8] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
                board.ledPwm9.setPulse(context.settings.channelPowers[9] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
                board.ledPwm10.setPulse(context.settings.channelPowers[10] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
                board.ledPwm11.setPulse(context.settings.channelPowers[11] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
                board.ledPwm12.setPulse(context.settings.channelPowers[12] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
                board.ledPwm13.setPulse(context.settings.channelPowers[13] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
            }
            break;
            case 1:
            {
                board.ledPwm1.setPulse(context.settings.channelPowers[index] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
            }
            break;
            case 2:
            {
                board.ledPwm2.setPulse(context.settings.channelPowers[index] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
            }
            break;
            case 3:
            {
                board.ledPwm3.setPulse(context.settings.channelPowers[index] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
            }
            break;
            case 4:
            {
                board.ledPwm4.setPulse(context.settings.channelPowers[index] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
            }
            break;
            case 5:
            {
                board.ledPwm5.setPulse(context.settings.channelPowers[index] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
            }
            break;
            case 6:
            {
                board.ledPwm6.setPulse(context.settings.channelPowers[index] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
            }
            break;
            case 7:
            {
                board.ledPwm7.setPulse(context.settings.channelPowers[index] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
            }
            break;
            case 8:
            {
                board.ledPwm8.setPulse(context.settings.channelPowers[index] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
            }
            break;
            case 9:
            {
                board.ledPwm9.setPulse(context.settings.channelPowers[index] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
            }
            break;
            case 10:
            {
                board.ledPwm10.setPulse(context.settings.channelPowers[index] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
            }
            break;
            case 11:
            {
                board.ledPwm11.setPulse(context.settings.channelPowers[index] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
            }
            break;
            case 12:
            {
                board.ledPwm12.setPulse(context.settings.channelPowers[index] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
            }
            break;
            case 13:
            {
                board.ledPwm13.setPulse(context.settings.channelPowers[index] * (static_cast<float>(context.settings.channelPowers[0]) / 100));
            }
            break;
        }
    }

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

    static void drawSave(Context& context)
    {
        auto& display = context.display;
        drawFrame(context.display);
        const char* str = "Saved!";

        u8 cursorX = (display.getWidth() - strlen(str) * (display.getFont().width + 1)) / 2;
        u8 cursorY = (display.getHeight() - display.getFont().height) / 2;

        display.setCursor(cursorX,
                          cursorY);
        display.print(str);
    }

    const Action onSave = [](Context& context) {
        apply(context);
        context.saveSettings();
    };
};

} // namespace statemachines
} // namepsace app