#pragma once

#define GPIO_IN_READ_DELAY 200
#define TIME_TO_LONG_PUSH 1000

#include "bsp/button.hpp"
#include "bsp/led.hpp"
#include "hal/core/backupRegisters.hpp"

namespace bsp
{

void BoardInit();

class Board
{
  public:
    Board();

    Button<Buttons::Left> leftButton;
    Button<Buttons::Right> rightButton;
    Button<Buttons::Up> upButton;
    Button<Buttons::Down> downButton;
    Button<Buttons::Select> selectButton;
    Button<Buttons::Back> backButton;

    Led<Leds::Led1> led;

    hal::core::BackupRegisters& registers;

  private:
    logger::Logger logger_;
};

} // namespace bsp
