// #include "app/menu.hpp"
// #include "gui/bufferedText.hpp"
// #include "gui/image.hpp"
// #include "gui/keys.hpp"
// #include "gui/moveCursor.hpp"
// #include "gui/text.hpp"
// #include "utils.hpp"


// namespace app
// {

// static gui::Text newLine("\n");
// static gui::Text colon(":");

// gui::BufferedText<4> MainMenu::dayPower;
// gui::BufferedText<4> MainMenu::nightPower;

// MainMenu::MainMenu(bsp::Board& board, IContext& context)
//     : mainMenu_("Main"), channelsMenu_("Channels"), currentMenu_(&mainMenu_), currentChannel_(0), context_(context)
// {
//     static gui::Text channelText("Channel");
//     static gui::Text generalText("General");
//     static gui::Text effectsText("Effects");
//     static gui::Text timeText("Time");
//     static gui::Text aboutText("About");


//     static gui::Option channel;
//     channel.next(&channelText).next(&newLine);
//     channel.onKey(gui::Keys::Select,
//                   [this]() {
//                       currentMenu_ = &channelsMenu_;
//                       currentMenu_->active(true);
//                   });


//     static gui::Option time;
//     time.next(&timeText).next(&newLine);
//     static gui::Option general;
//     general.next(&generalText).next(&newLine);
//     static gui::Option effects;
//     effects.next(&effectsText).next(&newLine);
//     static gui::Option about;
//     about.next(&aboutText).next(&newLine);

//     mainMenu_.addOption(channel);
//     mainMenu_.addOption(time);
//     mainMenu_.addOption(general);
//     mainMenu_.addOption(effects);
//     mainMenu_.addOption(about);

//     mainMenu_.active(true);
//     mainMenu_.onKey(gui::Keys::Back, [this] { mainMenu_.active(false); });
//     createChannelsMenu();
// }

// const char* getChannelName(int channel)
// {
//     switch (channel)
//     {
//         case 0:
//             return "Master";
//         case 1:
//             return "RB c";
//         case 2:
//             return "FS";
//         case 3:
//             return "RB r";
//         case 4:
//             return "8.5K";
//         case 5:
//             return "UV";
//         case 6:
//             return "RB l";
//         case 7:
//             return "RB c";
//         case 8:
//             return "G";
//         case 9:
//             return "8.5K";
//         case 10:
//             return "RB c";
//         case 11:
//             return "12K";
//         case 12:
//             return "DR";
//         case 13:
//             return "12K";
//         default:
//             return "Unknown";
//     }
//     return "Unknown";
// }

// void MainMenu::updatePage()
// {
//     utils::writeToBufferAligned(dayPower.data(), context_.getAllChannels()[currentChannel_].dayPower(), '\0', 3);
//     utils::writeToBufferAligned(nightPower.data(), context_.getAllChannels()[currentChannel_].nightPower(), '\0', 3);
// }

// void MainMenu::createChannelsMenu()
// {
//     // static gui::Text channelText("Ch ");
//     // static gui::BufferedText<3> channelNr;
//     // utils::writeToBufferAligned(channelNr.data(), currentChannel_, '\0');
//     // static gui::Text channelName(getChannelName(currentChannel_));


//     // static gui::Option channelOption;

//     // channelOption
//     //     .next(&channelText)
//     //     .next(&channelNr)
//     //     .next(&colon)
//     //     .next(&channelName)
//     //     .next(&newLine);

//     // channelOption.onKey(gui::Keys::Right, [this]() {
//     //     if (currentChannel_ < context_.getAllChannels().size() - 1)
//     //     {
//     //         ++currentChannel_;
//     //     }
//     //     else
//     //     {
//     //         currentChannel_ = 0;
//     //     }
//     //     utils::writeToBufferAligned(channelNr.data(), currentChannel_, '\0');
//     //     channelName.setText(getChannelName(currentChannel_));
//     //     updatePage();

//     // });

//     // channelOption.onKey(gui::Keys::Left, [this] {
//     //     if (currentChannel_ <= 0)
//     //     {
//     //         currentChannel_ = context_.getAllChannels().size() - 1;
//     //     }
//     //     else
//     //     {
//     //         --currentChannel_;
//     //     }
//     //     utils::writeToBufferAligned(channelNr.data(), currentChannel_, '\0');
//     //     channelName.setText(getChannelName(currentChannel_));
//     //     updatePage();

//     // });

//     // channelOption.visible(true);
//     // channelsMenu_.onKey(gui::Keys::Back,
//     //                     [this]() {
//     //                         currentMenu_ = &mainMenu_;
//     //                         currentMenu_->active(true);
//     //                     });

//     // static gui::Option power;
//     // static gui::Image dayImage(display::Images::Sun);
//     // auto imageDraw = [](const display::Image& image) {
//     //     display::Display& display = *display::Display::get();
//     //     display.decrementCursorY(1);
//     //     display.drawImage(image);
//     //     display.incrementCursorY(1);
//     //     display.incrementCursorX(2);
//     // };
//     // dayImage.setDraw(imageDraw);
//     // static gui::Image nightImage(display::Images::Moon);
//     // nightImage.setDraw(imageDraw);
//     // static gui::MoveCursor<4, 0> space;
//     // static gui::MoveCursor<0, 2> offsetY;
//     // static gui::Text daySuffix("%");
//     // static gui::Text nightSuffix("%");


//     // power.next(&dayImage)
//     //     .next(&dayPower)
//     //     .next(&daySuffix)
//     //     .next(&offsetY)
//     //     .next(&newLine);

//     //     power.height(power.height() + 2);
//     //     static gui::Option nightPower;
//     //     static gui::MoveCursor<0, 2> nightPowerOffsetY;

//     //     nightPower.next(&nightImage)
//     //         .next(&nightPower)
//     //         .next(&nightSuffix)
//     //         .next(&nightPowerOffsetY)
//     //         .next(&newLine);
//     //     nightPower.height(nightPower.height() + 2);

//     //     static gui::Option currentPower;
//     //     static gui::Text currentPowerText("C: 100%");
//     //     currentPower.next(&currentPowerText).next(&newLine);


//     //     static gui::Option sunriseTime;
//     //     static gui::Text sunriseText(" 00:00:00");
//     //     static gui::Text sunshineText(" 00:00:00");

//     //     static gui::Image sunriseImage(display::Images::Sun);
//     //     sunriseImage.setDraw(imageDraw);
//     //     static gui::Image sunshineImage(display::Images::Moon);
//     //     sunshineImage.setDraw(imageDraw);
//     //     static gui::MoveCursor<0, 1> nightOffsetY;

//     //     sunriseTime.next(&sunriseImage).next(&sunriseText).next(&nightOffsetY).next(&newLine);
//     //     sunriseTime.height(sunriseTime.height() + 1);

//     //     static gui::Option sunshineTime;
//     //     static gui::MoveCursor<4, 0> nightSpace;
//     //     sunshineTime.next(&sunshineImage).next(&nightSpace).next(&sunshineText).next(&newLine);


//     //     channelsMenu_.addOption(channelOption);
//     //     channelsMenu_.addOption(currentPower);
//     //     channelsMenu_.addOption(power);
//     //     channelsMenu_.addOption(nightPower);
//     //     channelsMenu_.addOption(sunriseTime);
//     //     channelsMenu_.addOption(sunshineTime);

//     //     updatePage();
//     // }
// }

// bool MainMenu::active() const
// {
//     return currentMenu_->active();
// }

// } // namespace app
