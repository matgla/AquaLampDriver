#include "app/app.hpp"
#include "app/context.hpp"
#include "bsp/board.hpp"
#include "display/display.hpp"
#include "display/font.hpp"


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
    app::App app(*display::Display::get(), board, context);
    app.start();
    app.run();

    return 0;
}
