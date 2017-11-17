#pragma once

#include "bsp/button.hpp"
#include "bsp/led.hpp"
#include "bsp/onewire.hpp"
#include "bsp/spi.hpp"
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
    Led<Leds::LcdBacklight> lcdBacklight;

    hal::core::BackupRegisters& registers;

    OneWire<OneWires::OneWire1> oneWire;

    Spi spi;

    void run();
    bool exit();

private:
    logger::Logger logger_;
};

} // namespace bsp
