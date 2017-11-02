#include "app.hpp"

#include "board.hpp"
#include "rtc/rtc.hpp"

App::App(Board& board)
    : logger_("App"),
      board_(board)
{
    logger_.info() << "Startup";
    rtc::Rtc::get().setSecondsHandler([this] {
        update();
    });

    board_.led.on();
    // board_.registers.startupDone();

    logger_.info() << "Started";
}

void App::update()
{
    statemachine_.process_event(events::Update{});
}

void App::run()
{
    while (true)
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
    }
}