#pragma once
#include <boost/sml.hpp>

#include "helpers.hpp"
#include "logger.hpp"
#include "stm32includes.hpp"
namespace sml = boost::sml;

// void* __dso_handle;

// void initializeBoardLeds()
// {
//     GPIO_InitTypeDef GPIO_InitStructure;
//     RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//     GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//     GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//     GPIO_Init(GPIOD, &GPIO_InitStructure);
// }

class Initial;
class Initialized;
class BootModeDetected;
class BootLoader;
class BootFw;

// clang-format off
struct evInitialize {};
struct evGetBootMode {};
struct evBoot {};
// clang-format on

enum class BootMode
{
    FW,
    BOOTLOAD
};

const auto initialize = [](Logger &logger) {
    logger << Level::INFO << "STM32 intialization ongoing\n";
    //  initializeBoardLeds();
    // GPIO_SetBits(GPIOD, GPIO_Pin_14);

};

const auto bootFw = [](Logger &logger) {
    logger << Level::INFO << "Booting firmware...\n";
};

const auto bootLoader = [](Logger &logger) {
    logger << Level::INFO << "Booting loader...\n";
};

class BootLoaderSm
{
    BootMode bootMode_;

  public:
    BootLoaderSm()
        : bootMode_(BootMode::BOOTLOAD)
    {
    }

    auto operator()() noexcept
    {
        using namespace sml;
        // clang-format off
        return make_transition_table(
            //|---------STATE----------|-----------EVENT-----------|-------GUARD--------|-----------------ACTION------------------|--------TARGET----------|//
              *state<Initial>          + event<evInitialize>                            / initialize                              = state<Initialized>,
               state<Initialized>      + event<evGetBootMode>                           / call(this, &BootLoaderSm::getBootMode)  = state<BootModeDetected>,
               state<BootModeDetected> + event<evBoot>              [call(this, &BootLoaderSm::boot_fw)]           / bootFw                                  = state<BootFw>,
               state<BootModeDetected> + event<evBoot>              [call(this, &BootLoaderSm::boot_loader)]       / bootLoader                              = state<BootLoader>
        );
        // clang-format on
    }

    // actions

    bool boot_fw()
    {
        return bootMode_ == BootMode::FW;
    }

    bool boot_loader()
    {
        return bootMode_ == BootMode::BOOTLOAD;
    }

    void getBootMode(Logger &logger)
    {
        logger << Level::INFO << "Obtaining boot mode\n";
    }
};