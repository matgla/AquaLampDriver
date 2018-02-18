// #include "app/channelMenu.hpp"

// #include "hal/time/sleep.hpp"

// namespace app
// {

// ChannelMenu::ChannelMenu(display::Display& display, bsp::Board& board, IContext& context)
//     : display_(display),
//       board_(board),
//       context_(context),
//       currentChannel_(0),
//       selection_(1),
//       state_(ChannelMenu::State::Close),
//       subState_(ChannelMenu::SubState::None)
// {
// }

// void ChannelMenu::start()
// {
//     state_ = State::ChannelSelect;
// }

// void ChannelMenu::onChangePower()
// {
//     if (subState_ == SubState::None)
//     {
//         if (board_.downButton.isPressed())
//         {
//             state_ = State::SetDayTime;
//             return;
//         }

//         if (board_.upButton.isPressed())
//         {
//             state_ = State::ChannelSelect;
//             return;
//         }

//         if (board_.rightButton.isPressed())
//         {
//             subState_ = SubState::ChangeDayPower;
//             return;
//         }
//     }
//     else if (subState_ == SubState::ChangeDayPower)
//     {
//         onChangeDayPower();
//     }
//     else if (subState_ == SubState::ChangeNightPower)
//     {
//         onChangeNightPower();
//     }
// }

// void ChannelMenu::onSetDayTime()
// {

//     if (subState_ == SubState::None)
//     {
//         if (board_.downButton.isPressed())
//         {
//             state_ = State::SetNightTime;
//             return;
//         }

//         if (board_.upButton.isPressed())
//         {
//             state_ = State::ChangePower;
//             return;
//         }

//         if (board_.rightButton.isPressed())
//         {
//             subState_ = SubState::SetHours;
//             return;
//         }
//     }

//     if (subState_ == SubState::SetHours)
//     {
//         if (board_.rightButton.isPressed())
//         {
//             subState_ = SubState::SetMinutes;
//             return;
//         }

//         if (board_.leftButton.isPressed())
//         {
//             subState_ = SubState::None;
//             return;
//         }

//         if (board_.upButton.isPressed())
//         {
//             auto& hour = context_.getAllChannels()[currentChannel_].getSunriseTime().hour();
//             if (hour < 24)
//             {
//                 ++hour;
//             }
//             return;
//         }

//         if (board_.upButton.isLongPressed())
//         {
//             auto& hour = context_.getAllChannels()[currentChannel_].getSunriseTime().hour();

//             hour += 5;
//             if (hour > 24)
//             {
//                 hour = 24;
//             }

//             return;
//         }

//         if (board_.downButton.isPressed())
//         {
//             auto& hour = context_.getAllChannels()[currentChannel_].getSunriseTime().hour();
//             if (hour > 0)
//             {
//                 --hour;
//             }
//             return;
//         }

//         if (board_.downButton.isLongPressed())
//         {
//             auto& hour = context_.getAllChannels()[currentChannel_].getSunriseTime().hour();
//             if (hour <= 5)
//             {
//                 hour = 0;
//             }
//             else
//             {
//                 hour -= 5;
//             }
//             return;
//         }
//     }

//     if (subState_ == SubState::SetMinutes)
//     {
//         if (board_.rightButton.isPressed())
//         {
//             subState_ = SubState::SetSeconds;
//             return;
//         }

//         if (board_.leftButton.isPressed())
//         {
//             subState_ = SubState::SetHours;
//             return;
//         }

//         if (board_.upButton.isPressed())
//         {
//             auto& hour = context_.getAllChannels()[currentChannel_].getSunriseTime().minute();
//             if (hour < 24)
//             {
//                 ++hour;
//             }
//             return;
//         }

//         if (board_.upButton.isLongPressed())
//         {
//             auto& hour = context_.getAllChannels()[currentChannel_].getSunriseTime().minute();

//             hour += 5;
//             if (hour > 24)
//             {
//                 hour = 24;
//             }

//             return;
//         }

//         if (board_.downButton.isPressed())
//         {
//             auto& hour = context_.getAllChannels()[currentChannel_].getSunriseTime().minute();
//             if (hour > 0)
//             {
//                 --hour;
//             }
//             return;
//         }

//         if (board_.downButton.isLongPressed())
//         {
//             auto& hour = context_.getAllChannels()[currentChannel_].getSunriseTime().minute();
//             if (hour <= 5)
//             {
//                 hour = 0;
//             }
//             else
//             {
//                 hour -= 5;
//             }
//             return;
//         }
//     }

//     if (subState_ == SubState::SetSeconds)
//     {
//         if (board_.leftButton.isPressed())
//         {
//             subState_ = SubState::SetMinutes;
//             return;
//         }

//         if (board_.upButton.isPressed())
//         {
//             auto& hour = context_.getAllChannels()[currentChannel_].getSunriseTime().second();
//             if (hour < 24)
//             {
//                 ++hour;
//             }
//             return;
//         }

//         if (board_.upButton.isLongPressed())
//         {
//             auto& hour = context_.getAllChannels()[currentChannel_].getSunriseTime().second();

//             hour += 5;
//             if (hour > 24)
//             {
//                 hour = 24;
//             }

//             return;
//         }

//         if (board_.downButton.isPressed())
//         {
//             auto& hour = context_.getAllChannels()[currentChannel_].getSunriseTime().second();
//             if (hour > 0)
//             {
//                 --hour;
//             }
//             return;
//         }

//         if (board_.downButton.isLongPressed())
//         {
//             auto& hour = context_.getAllChannels()[currentChannel_].getSunriseTime().second();
//             if (hour <= 5)
//             {
//                 hour = 0;
//             }
//             else
//             {
//                 hour -= 5;
//             }
//             return;
//         }
//     }
// }

// void ChannelMenu::onSetNightTime()
// {
//     if (board_.downButton.isPressed())
//     {
//         state_ = State::ChannelSelect;
//         return;
//     }

//     if (board_.upButton.isPressed())
//     {
//         state_ = State::SetDayTime;
//         return;
//     }
// }

// void ChannelMenu::changePower(u8& power)
// {
//     if (board_.upButton.isPressed())
//     {
//         if (power + 1 >= 100)
//         {
//             power = 100;
//             return;
//         }
//         power += 1;
//         return;
//     }
//     if (board_.downButton.isPressed())
//     {
//         if (power <= 1)
//         {
//             power = 0;
//             return;
//         }
//         power -= 1;
//         return;
//     }

//     if (board_.upButton.isLongPressed())
//     {
//         hal::time::msleep(100);
//         if (power + 5 >= 100)
//         {
//             power = 100;
//             return;
//         }
//         power += 5;
//         return;
//     }
//     if (board_.downButton.isLongPressed())
//     {
//         hal::time::msleep(100);
//         if (power <= 5)
//         {
//             power = 0;
//             return;
//         }
//         power -= 5;
//         return;
//     }
// }

// void ChannelMenu::onChangeDayPower()
// {

//     if (board_.leftButton.isPressed())
//     {
//         subState_ = SubState::None;
//         return;
//     }

//     if (board_.rightButton.isPressed())
//     {
//         subState_ = SubState::ChangeNightPower;
//         return;
//     }

//     changePower(context_.getAllChannels()[currentChannel_].dayPower());
// }

// void ChannelMenu::onChangeNightPower()
// {
//     if (board_.leftButton.isPressed())
//     {
//         subState_ = SubState::ChangeDayPower;
//         return;
//     }
//     changePower(context_.getAllChannels()[currentChannel_].nightPower());
// }

// ChannelMenu::State ChannelMenu::run()
// {
//     if (board_.backButton.isPressed())
//     {
//         return ChannelMenu::State::Close;
//     }

//     switch (state_)
//     {
//         case State::ChannelSelect:
//             onChannelSelect();
//             break;
//         case State::ChangePower:
//             onChangePower();
//             break;
//         case State::SetDayTime:
//             onSetDayTime();
//             break;
//         case State::SetNightTime:
//             onSetNightTime();
//             break;
//         case State::Close:
//             break;
//     }

//     onShow();
//     return state_;
// }

// void ChannelMenu::onChannelSelect()
// {
//     if (board_.leftButton.isPressed())
//     {
//         if (currentChannel_ == 0)
//         {
//             currentChannel_ = 13;
//             return;
//         }
//         --currentChannel_;
//         return;
//     }

//     if (board_.rightButton.isPressed())
//     {
//         if (currentChannel_ == 13)
//         {
//             currentChannel_ = 0;
//             return;
//         }
//         ++currentChannel_;
//         return;
//     }

//     if (board_.upButton.isPressed())
//     {
//         state_ = State::SetNightTime;
//         return;
//     }

//     if (board_.downButton.isPressed())
//     {
//         state_ = State::ChangePower;
//         return;
//     }
// }

// void ChannelMenu::drawPrefix(State state)
// {
//     if (state_ == state)
//     {
//         display_.drawImage(display::Images::fullTriangle);
//     }
//     else
//     {
//         display_.drawImage(display::Images::emptyTriangle);
//     }
//     display_.incrementCursorX(1);
// }

// void ChannelMenu::onShow()
// {
//     display_.clear(display::Colors::OFF);
//     drawPrefix(State::ChannelSelect);
//     char buffer[5];
//     display_.print("Channel: ");

//     if (currentChannel_ == 0)
//     {
//         display_.print(" M\n");
//     }
//     else
//     {
//         utils::writeToBufferAligned(buffer, currentChannel_, '\0', 2, ' ');
//         display_.print(buffer);
//         display_.print("\n");
//     }
//     // display_.print("    D    N\n");
//     display_.incrementCursorY(2);

//     drawPrefix(State::ChangePower);

//     utils::writeToBufferAligned(buffer, context_.getAllChannels()[currentChannel_].dayPower(), '\0', 3, ' ');
//     display_.print("P:");
//     display_.decrementCursorY(2);
//     display_.drawImage(display::Images::Sun);
//     display_.incrementCursorY(2);
//     display_.incrementCursorX(2);

//     if (subState_ == SubState::ChangeDayPower)
//     {
//         display_.print(buffer, display::Colors::BLACK, display::Display::Style::Underscore);
//     }
//     else
//     {
//         display_.print(buffer);
//     }
//     display_.print("%");

//     display_.incrementCursorX(2);
//     display_.decrementCursorY(2);
//     display_.drawImage(display::Images::Moon);
//     display_.incrementCursorY(2);
//     display_.incrementCursorX(1);

//     utils::writeToBufferAligned(buffer, context_.getAllChannels()[currentChannel_].nightPower(), '\0', 3, ' ');

//     if (subState_ == SubState::ChangeNightPower)
//     {
//         display_.print(buffer, display::Colors::BLACK, display::Display::Style::Underscore);
//     }
//     else
//     {
//         display_.print(buffer);
//     }
//     display_.print("%\n");

//     display_.incrementCursorY(1);
//     drawPrefix(State::SetDayTime);
//     display_.drawImage(display::Images::Sun);
//     display_.incrementCursorY(2);
//     if (currentChannel_ == 0)
//     {
//         utils::writeToBufferAligned(buffer, context_.masterChannel().getSunriseTime().hour(), '\0', 2, '0');
//         display_.print(" ");
//         if (subState_ == SubState::SetHours && state_ == State::SetDayTime)
//         {
//             display_.print(buffer, display::Colors::BLACK, display::Display::Style::Underscore);
//         }
//         else
//         {
//             display_.print(buffer);
//         }
//         display_.print(":");

//         utils::writeToBufferAligned(buffer, context_.masterChannel().getSunriseTime().minute(), '\0', 2, '0');
//         if (subState_ == SubState::SetMinutes && state_ == State::SetDayTime)
//         {
//             display_.print(buffer, display::Colors::BLACK, display::Display::Style::Underscore);
//         }
//         else
//         {
//             display_.print(buffer);
//         }
//         display_.print(":");

//         utils::writeToBufferAligned(buffer, context_.masterChannel().getSunriseTime().second(), '\0', 2, '0');
//         if (subState_ == SubState::SetSeconds && state_ == State::SetDayTime)
//         {
//             display_.print(buffer, display::Colors::BLACK, display::Display::Style::Underscore);
//         }
//         else
//         {
//             display_.print(buffer);
//         }
//         display_.print("\n");
//     }
//     // display_.print(" 00:00:00\n");
//     drawPrefix(State::SetNightTime);
//     display_.drawImage(display::Images::Moon);
//     display_.incrementCursorY(1);
//     display_.incrementCursorX(4);
//     display_.print(" 00:00:00\n");
//     display_.setY(48 - display::Images::backIcon.height);
//     display_.setX(2);
//     display_.drawImage(display::Images::backIcon);
//     display_.setX(84 - display::Images::selectIcon.width - 2);
//     display_.drawImage(display::Images::selectIcon);
// }

// } // namespace app
