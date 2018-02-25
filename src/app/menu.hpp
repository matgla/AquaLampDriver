// #pragma once

// #include <cstdint>


// #include "app/channelMenu.hpp"
// #include "app/contextInterface.hpp"
// #include "bsp/board.hpp"
// #include "display/display.hpp"
// // #include "gui/bufferedText.hpp"
// // #include "gui/keys.hpp"

// namespace app
// {

// class MainMenu
// {
// public:
//     MainMenu(bsp::Board& board, IContext& context);

//     void run(gui::Keys key, bool isLongPressed)
//     {
//         if (!currentMenu_->active())
//         {
//             currentMenu_->active(true);
//         }
//         currentMenu_->run(key, isLongPressed);
//     }

//     bool active() const;
//     void updatePage();

// protected:
//     void createChannelsMenu();

//     gui::Menu<6> mainMenu_;
//     gui::Menu<6> channelsMenu_;
//     gui::Element* currentMenu_;
//     int currentChannel_;
//     IContext& context_;
//     static gui::BufferedText<4> dayPower;
//     static gui::BufferedText<4> nightPower;
// };

// } // namespace app
