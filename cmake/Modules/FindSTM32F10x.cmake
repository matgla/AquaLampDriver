# Find the STM32 CMSIS and StdPeriph libraries

set(STM32_LIBRARY_ROOT_DIR $ENV{STM32_LIBRARY_ROOT_DIR})

file(TO_CMAKE_PATH $ENV{STM32_LIBRARY_ROOT_DIR} STM32_LIBRARY_ROOT_DIR_CONVERTED)
set(STM32_LIBRARY_ROOT_DIR ${STM32_LIBRARY_ROOT_DIR_CONVERTED} CACHE PATH "Path to STM32 library" FORCE)


find_path(STM32_LIBRARY_ROOT_DIR
    CMSIS/Include/core_cm4.h
    STM32F10x_StdPeriph_Driver/inc
    DOC "STM32 libraries root directory: STM32F10x_DSP_StdPeriph_Lib_V1.0.1/Libraries"
)

message("-- Library root ${STM32_LIBRARY_ROOT_DIR}")

set(STM32_STARTUP_SOURCE ${STM32_LIBRARY_ROOT_DIR}/stm32f1/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_md.s)

set(STM32_INCLUDE_DIRS
    ${STM32_LIBRARY_ROOT_DIR}/stm32f1/Libraries/STM32F10x_StdPeriph_Driver/inc/
    ${STM32_LIBRARY_ROOT_DIR}/stm32f1/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/
    ${STM32_LIBRARY_ROOT_DIR}/stm32f1/Libraries/CMSIS/CM3/CoreSupport/
)

set(SOURCES_DIR ${STM32_LIBRARY_ROOT_DIR}/stm32f1/Libraries/STM32F10x_StdPeriph_Driver/src/)

file(GLOB STM32_SOURCES ${SOURCES_DIR}/misc.c
                        ${SOURCES_DIR}/stm32f10x_gpio.c
                        ${SOURCES_DIR}/stm32f10x_flash.c
                        ${SOURCES_DIR}/stm32f10x_usart.c
                        ${SOURCES_DIR}/stm32f10x_rcc.c
                        ${SOURCES_DIR}/stm32f10x_tim.c
                        ${SOURCES_DIR}/stm32f10x_rtc.c
                        ${SOURCES_DIR}/stm32f10x_pwr.c
                        ${SOURCES_DIR}/stm32f10x_bkp.c
                        ${SOURCES_DIR}/stm32f10x_exti.c
                        ${SOURCES_DIR}/stm32f10x_spi.c
                        ${STM32_STARTUP_SOURCE})

find_package(PackageHandleStandardArgs)
find_package_handle_standard_args(CMSIS DEFAULT_MSG
        STM32_LIBRARY_ROOT_DIR
        STM32_STARTUP_SOURCE
        STM32_SOURCES
        STM32_INCLUDE_DIRS
        )

