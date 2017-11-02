#include "app.hpp"

#include "board.hpp"
#include "rtc/rtc.hpp"

App::App(Board& board)
    : channelSettings_(board),
      statemachine_(channelSettings_),
      logger_("App"),
      board_(board)
{
    logger_.info() << "Startup";
    rtc::Rtc::get().setSecondsHandler([this] {
        update();
    });

    board_.led.on();
    board_.registers.startupDone();

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

void printfMenu(int selected)
{
    printf("\e[2J");
    if (selected == 1)
    {
        printf("-> ");
    }
    else
    {
        printf("   ");
    }
    printf("1. Channel Settings\n");
    if (selected == 2)
    {
        printf("-> ");
    }
    else
    {
        printf("   ");
    }
    printf("2. Time Settings\n");
    if (selected == 3)
    {
        printf("-> ");
    }
    else
    {
        printf("   ");
    }
    printf("3. General Settings\n");
    if (selected == 4)
    {
        printf("-> ");
    }
    else
    {
        printf("   ");
    }
    printf("4. Effect Settings\n");
    if (selected == 5)
    {
        printf("-> ");
    }
    else
    {
        printf("   ");
    }
    printf("5. About Settings\n");
}