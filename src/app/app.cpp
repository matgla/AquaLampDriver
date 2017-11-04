#include "app/app.hpp"

#include "app/statemachines/events.hpp"
#include "bsp/board.hpp"
#include "hal/time/rtc.hpp"

namespace app
{
App::App(bsp::Board& board)
    : channelSettings_(board),
      statemachine_(channelSettings_),
      logger_("App"),
      board_(board)
{
    logger_.info() << "Startup";
    hal::time::Rtc::get().setSecondsHandler([this] {
        update();
    });

    board_.led.on();
    board_.registers.startupDone();

    logger_.info() << "Started";
    display_.print("Hello world\n");
    display_.print("CH1: 100%\n");
}

void App::update()
{
    statemachine_.process_event(statemachines::events::Update{});
}

void App::run()
{
    using namespace statemachines;
    while (!board_.exit())
    {
        if (board_.downButton.isPressed())
        {
            statemachine_.process_event(events::ButtonDown{});
        }
        if (board_.upButton.isPressed())
        {
            statemachine_.process_event(events::ButtonUp{});
        }
        if (board_.leftButton.isPressed())
        {
            statemachine_.process_event(events::ButtonLeft{});
        }
        if (board_.rightButton.isPressed())
        {
            statemachine_.process_event(events::ButtonRight{});
        }
        if (board_.selectButton.isPressed())
        {
            statemachine_.process_event(events::ButtonSelect{});
        }
        if (board_.backButton.isPressed())
        {
            statemachine_.process_event(events::ButtonBack{});
        }

        board_.run();
    }
}

} // namespace app
