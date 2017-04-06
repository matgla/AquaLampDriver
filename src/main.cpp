#include "stm32f4xx.h"
#include <boost/sml.hpp>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include "kernel.hpp"
#include "logger.hpp"
#include "state_machine/bootloader_sm.hpp"
#include "types.h"
#include "utils.hpp"
#include "usart.hpp"

#include "tasking.h"


// namespace sml = boost::sml;

// struct release
// {
// };
// struct ack
// {
// };
// struct fin
// {
// };
// struct timeout
// {
// };

// const auto is_ack_valid = [](const ack&) { return true; };
// const auto is_fin_valid = [](const fin&) { return true; };

// const auto send_fin = [] {};
// const auto send_ack = [] {};

// class established;
// class fin_wait_1;
// class fin_wait_2;
// class timed_wait;

// struct hello_world
// {
//     auto operator()() const
//     {
//         using namespace sml;
//         return make_transition_table(
//             *state<established> + event<release> / send_fin = state<fin_wait_1>,
//             state<fin_wait_1> + event<ack>[is_ack_valid] = state<fin_wait_2>,
//             state<fin_wait_2> + event<fin>[is_fin_valid] / send_ack = state<timed_wait>,
//             state<timed_wait> + event<timeout> / send_ack = X);
//     }
// };

Logger l1("WUNTEK1");
Logger l2("WUNTEK2");

void handler1()
{
    while(true)
    {
         //l1 << Level::INFO << "Wontek 1\n";
         printf("wontek1\n");
         DelayS(1);
    }
}

void handler2()
{
    while(true)
    {
        printf("wontek2\n");
        DelayS(1);

    }
}

int main(void)
{
    SystemInit();
    //hw::USART<hw::USARTS::USART2_PP1>::getUsart();
    hw::USART<hw::USARTS::USART1_PP1>::getUsart();
    //u1.init();

    Logger logger("boot\0");
    // initializeBoardLeds();
    // GPIO_SetBits(GPIOD, GPIO_Pin_14);

    hardwareInitialize();
    
    task t1, t2;
    initialize_t();

    configureTask(&t1, (u32)handler1);
    configureTask(&t2, (u32)handler2);


    addTaskToList(&t1);
    addTaskToList(&t2);

    initializeMultiTasking();
    
    
    boost::sml::sm<BootLoaderSm> sm{logger};

    sm.process_event(evInitialize{});
    sm.process_event(evGetBootMode{});
    sm.process_event(evBoot{});
    // BootLoader bl(logger);
    //logger << Level::INFO << "Bootloader started\r";

    //logger << Level::INFO << "allocated on: " << (int)test << "\n";

    /*if (bl.specialMode())
    {
        logger << Level::INFO << "Boot in special mode\n";
        bl.bootSpecialMode();
    }
    else
    {
        logger << Level::INFO << "Boot FW\n";
        bl.bootFW();
    }*/

    // sml::sm<hello_world> sm;

    // sm.process_event(release{});

    // sm.process_event(ack{});

    // sm.process_event(fin{});

    // sm.process_event(timeout{});

    while (1)
    {
    }
}


void assert_failed(u8* file, u32 line)
{
    write(0, file, strlen((char*)file));
    write(0, ":", 1);
    char buf[10];
    utils::itoa(line, buf, 10);
    write(0, buf, strlen(buf));
    write(0, " assertion failed!", 18);
    while (true)
    {
    }
}
