#pragma once

#include "bsp/button.hpp"
#include "bsp/led.hpp"
#include "bsp/onewire.hpp"
#include "bsp/pwm.hpp"
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
    Button<Buttons::Down> downButton;
    Button<Buttons::Right> rightButton;
    Button<Buttons::Select> selectButton;
    Button<Buttons::Up> upButton;
    Button<Buttons::Back> backButton;

    Led<Leds::Led1> led;
    Led<Leds::LcdBacklight> lcdBacklight;

    hal::core::BackupRegisters& registers;

    OneWire<OneWires::OneWire1> oneWire;

    Spi spi;

    Pwm<Channels::Channel1> ledPwm1;
    Pwm<Channels::Channel2> ledPwm2;
    Pwm<Channels::Channel3> ledPwm3;
    Pwm<Channels::Channel4> ledPwm4;
    Pwm<Channels::Channel5> ledPwm5;
    Pwm<Channels::Channel6> ledPwm6;
    Pwm<Channels::Channel7> ledPwm7;
    Pwm<Channels::Channel8> ledPwm8;
    Pwm<Channels::Channel9> ledPwm9;
    Pwm<Channels::Channel10> ledPwm10;
    Pwm<Channels::Channel11> ledPwm11;
    Pwm<Channels::Channel12> ledPwm12;
    Pwm<Channels::Channel13> ledPwm13;
    Pwm<Channels::Channel14> fanDriver;
    Pwm<Channels::Channel15> fanPwm1;
    Pwm<Channels::Channel16> fanPwm2;

    void run();
    bool exit();

private:
    logger::Logger logger_;
};

} // namespace bsp
