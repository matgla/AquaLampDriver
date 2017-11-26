set(COMMON_SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(STM32_SRC_DIR "${PROJECT_SOURCE_DIR}/src/hal/stm32")
set(DRIVERS_SRC_DIR "${PROJECT_SOURCE_DIR}/src/drivers")

set(stm32_sources
    ${COMMON_SRC_DIR}/stm32f10x_it.cpp
    ${COMMON_SRC_DIR}/system_stm32f10x.c
    ${COMMON_SRC_DIR}/syscalls.cpp
    ${COMMON_SRC_DIR}/usart.cpp

    ${STM32_SRC_DIR}/core/core_stm32.cpp    
    ${STM32_SRC_DIR}/core/criticalSection_stm32.cpp    
    ${STM32_SRC_DIR}/core/backupRegisters_stm32.cpp    
    ${STM32_SRC_DIR}/time/sleep_stm32.cpp 
    ${STM32_SRC_DIR}/time/rtc_stm32.cpp
    ${STM32_SRC_DIR}/time/time_stm32.cpp  
    ${STM32_SRC_DIR}/time/watchdog_stm32.cpp
    ${STM32_SRC_DIR}/utils/assert_stm32.cpp
    ${STM32_SRC_DIR}/memory/eeprom_stm32.cpp
)

set(stm32_includes
    ${COMMON_SRC_DIR}/stm32f10x_conf.h
    ${COMMON_SRC_DIR}/stm32f10x_it.hpp
    ${COMMON_SRC_DIR}/syscall.hpp
    ${COMMON_SRC_DIR}/usart.hpp
    ${COMMON_SRC_DIR}/usart.hpp
)
