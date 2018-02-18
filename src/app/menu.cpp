#include "app/menu.hpp"
#include "gui/text.hpp"


namespace app
{

MainMenu::MainMenu(bsp::Board& board, IContext& context)
    : gui::Menu<5>("Main"), channelsMenu_("Channels"), currentMenu_(this)
{
    static gui::Text channelText("Channel");
    static gui::Text generalText("General");
    static gui::Text effectsText("Effects");
    static gui::Text timeText("Time");
    static gui::Text aboutText("About");


    static gui::Option channel;
    channel.next(&channelText);
    static gui::Option time;
    time.next(&timeText);
    static gui::Option general;
    general.next(&generalText);
    static gui::Option effects;
    effects.next(&effectsText);
    static gui::Option about;
    about.next(&aboutText);

    addOption(channel);
    addOption(time);
    addOption(general);
    addOption(effects);
    addOption(about);
}

void MainMenu::createChannelsMenu()
{
    // Option
    //     channelsMenu_
}

// void Menu::onShow()
// {
//     display_.clear(display::Colors::OFF);
//     drawPrefix(1);
//     display_.print("1.Channel\n");
//     drawPrefix(2);
//     display_.print("2.Time\n");
//     drawPrefix(3);
//     display_.print("3.General\n");
//     drawPrefix(4);
//     display_.print("4.Effects\n");
//     drawPrefix(5);
//     display_.print("5.About\n");
//     display_.setY(48 - display::Images::backIcon.height);
//     display_.setX(2);
//     display_.drawImage(display::Images::backIcon);
//     display_.setX(84 - display::Images::selectIcon.width - 2);
//     display_.drawImage(display::Images::selectIcon);
// }

// void Menu::onSelect()
// {
//     switch (selection_)
//     {
//         case 1:
//             channelMenu_.start();
//             channelMenu_.run();
//             state_ = State::ChannelMenu;
//             break;
//         case 2:
//             break;
//         case 3:
//             break;
//         case 4:
//             break;
//         case 5:
//             break;
//     }
// }

// void Menu::drawPrefix(uint8_t selection)
// {
//     if (selection_ == selection)
//     {
//         display_.drawImage(display::Images::fullTriangle);
//     }
//     else
//     {
//         display_.drawImage(display::Images::emptyTriangle);
//     }
//     display_.incrementCursorX(1);
// }

// void Menu::start()
// {
//     state_ = State::Running;
// }

// void Menu::onRun()
// {
//     menu_.draw();
//     // if (board_.backButton.isPressed())
//     // {
//     //     state_ = State::Close;
//     // }
//     // if (board_.downButton.isPressed())
//     // {
//     //     if (selection_ >= 5)
//     //     {
//     //         selection_ = 1;
//     //     }
//     //     else
//     //     {
//     //         ++selection_;
//     //     }
//     // }

//     // if (board_.upButton.isPressed())
//     // {
//     //     if (selection_ == 1)
//     //     {
//     //         selection_ = 5;
//     //     }
//     //     else
//     //     {
//     //         --selection_;
//     //     }
//     // }

//     // if (board_.selectButton.isPressed())
//     // {
//     //     onSelect();
//     // }
//     // onShow();
// }


} // namespace app
