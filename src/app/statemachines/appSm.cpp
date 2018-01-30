// #include <cstdio>
// #include <ctime>
// #include <functional>

// #include "app/statemachines/appSm.hpp"

// namespace app
// {
// namespace statemachines
// {


// void AppSm::process_event(const events::Update& event)
// {
//     UNUSED(event);
//     switch (state_)
//     {
//         case States::DisplayInfo:
//         {
//             displayTime();
//         }
//         break;
//         case States::Menu:
//         {
//         }
//         break;
//     }
// }

// void AppSm::process_event(const events::ButtonBack& event)
// {
//     UNUSED(event);
//     switch (state_)
//     {
//         case States::DisplayInfo:
//         {
//             state_ = States::
//         }
//         break;
//         case States::Menu:
//         {
//         }
//         break;
//     }
// }

// void AppSm::process_event(const events::Update& event)
// {
//     UNUSED(event);
//     switch (state_)
//     {
//         case States::DisplayInfo:
//         {
//             displayTime();
//         }
//         break;
//         case States::Menu:
//         {
//         }
//         break;
//     }
// }

// void AppSm::process_event(const events::Update& event)
// {
//     UNUSED(event);
//     switch (state_)
//     {
//         case States::DisplayInfo:
//         {
//             displayTime();
//         }
//         break;
//         case States::Menu:
//         {
//         }
//         break;
//     }
// }

// void AppSm::process_event(const events::Update& event)
// {
//     UNUSED(event);
//     switch (state_)
//     {
//         case States::DisplayInfo:
//         {
//             displayTime();
//         }
//         break;
//         case States::Menu:
//         {
//         }
//         break;
//     }
// }

// void AppSm::process_event(const events::Update& event)
// {
//     UNUSED(event);
//     switch (state_)
//     {
//         case States::DisplayInfo:
//         {
//             displayTime();
//         }
//         break;
//         case States::Menu:
//         {
//         }
//         break;
//     }
// }

// void AppSm::displayTime()
// {
//     // context_.display.clear(display::Colors::OFF);
//     constexpr const int TimeBufferSize = 12;
//     constexpr const int DateBufferSize = 10;
//     char timeBuffer[TimeBufferSize];
//     char dateBuffer[DateBufferSize];
//     auto t                 = std::time(nullptr);
//     struct tm* currentTime = std::localtime(&t);
//     utils::formatDate(dateBuffer, DateBufferSize, currentTime);
//     utils::formatTime(timeBuffer, TimeBufferSize, currentTime);
//     // context_.display.print("    ");
//     // context_.display.print(dateBuffer);
//     // context_.display.print("    \n");
//     // context_.display.print(timeBuffer);
// }


// } // namespace statemachines
// } // namepsace app