#include <msgui/Font.hpp>
#include <msgui/GraphicDriver.hpp>
#include <msgui/Gui.hpp>

#include "app/app.hpp"
#include "app/context.hpp"
#include "bsp/board.hpp"
#include "display/display.hpp"
#include "display/font.hpp"
// #include "gui/graphicDriver.hpp"


// TODO: remove this ugly preprocessor

#ifdef PCD8544_DISPLAY
#include "drivers/lcd/pcd8544/displayPcd8544.hpp"
#elif SFML_DISPLAY
#include "drivers/lcd/sfml/displaySfml.hpp"
#endif

int main()
{
    bsp::BoardInit();
    bsp::Board board;

#ifdef PCD8544_DISPLAY
    drivers::lcd::DisplayPcd8544 lcdDriver(board);
#elif SFML_DISPLAY
    drivers::lcd::DisplaySfml lcdDriver;
#endif
    display::Display::initialize(board, lcdDriver, display::font_5x7);
    app::Context context(board, *display::Display::get());
    msgui::GraphicDriver driver(
        [&lcdDriver](int x, int y, bool enable) {
            display::Colors color = enable ? display::Colors::BLACK : display::Colors::OFF;
            lcdDriver.setPixel(x, y, color);
            lcdDriver.display();
        },
        [&lcdDriver] { return lcdDriver.getWidth(); },
        [&lcdDriver] { return lcdDriver.getHeight(); },
        [&lcdDriver] { lcdDriver.display(); });

    msgui::Gui::get().setDriver(driver);

    app::App app(*display::Display::get(), board, context);
    app.start();
    app.run();

    return 0;
}