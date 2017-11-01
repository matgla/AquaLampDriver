#include "app.hpp"

App::App()
    : logger_("app")
{
}

void App::pressButton(const Buttons& button)
{
    switch (button)
    {
        case Buttons::Back:
        {
            statemachine_.process_event(events::ButtonBack{});
        }
        break;
        case Buttons::Select:
        {
            statemachine_.process_event(events::ButtonSelect{});
        }
        break;
        case Buttons::Up:
        {
            statemachine_.process_event(events::ButtonUp{});
        }
        break;
        case Buttons::Down:
        {
            statemachine_.process_event(events::ButtonDown{});
        }
        break;
        case Buttons::Left:
        {
            statemachine_.process_event(events::ButtonLeft{});
        }
        break;
        case Buttons::Right:
        {
            statemachine_.process_event(events::ButtonRight{});
        }
    }
}

void App::run()
{
    statemachine_.process_event(events::Update{});
}