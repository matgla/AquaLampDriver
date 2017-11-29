set(COMMON_SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(DRIVERS_SRC_DIR "${PROJECT_SOURCE_DIR}/src/drivers")

set(common_porting_sources
    ${COMMON_SRC_DIR}/app/app.cpp
    ${COMMON_SRC_DIR}/main.cpp
    ${COMMON_SRC_DIR}/logger/logger.cpp
    ${COMMON_SRC_DIR}/timer/intervalTimer.cpp
    ${COMMON_SRC_DIR}/timer/timeoutTimer.cpp
    ${COMMON_SRC_DIR}/utils.cpp

    ${COMMON_SRC_DIR}/display/font.cpp
    ${COMMON_SRC_DIR}/display/images.cpp
    ${COMMON_SRC_DIR}/display/display.cpp

    ${DRIVERS_SRC_DIR}/lcd/pcd8544/displayPcd8544.cpp
    ${DRIVERS_SRC_DIR}/devices/ds18b20.cpp
)

set(common_porting_includes
    ${COMMON_SRC_DIR}/app/app.hpp
    ${COMMON_SRC_DIR}/app/context.hpp
    ${COMMON_SRC_DIR}/app/timeSetting.hpp
    ${COMMON_SRC_DIR}/app/statemachines/appSm.hpp
    ${COMMON_SRC_DIR}/app/statemachines/channelSettingsSm.hpp
    ${COMMON_SRC_DIR}/app/statemachines/timeSettingsSm.hpp
    ${COMMON_SRC_DIR}/app/statemachines/setTimeSm.hpp
    ${COMMON_SRC_DIR}/app/statemachines/events.hpp
    ${COMMON_SRC_DIR}/app/statemachines/helpers.hpp
    ${COMMON_SRC_DIR}/app/statemachines/menuSm.hpp
    ${COMMON_SRC_DIR}/app/statemachines/states.hpp

    ${COMMON_SRC_DIR}/hal/core/core.hpp
    ${COMMON_SRC_DIR}/hal/core/criticalSection.hpp
    ${COMMON_SRC_DIR}/hal/core/backupRegisters.hpp
    ${COMMON_SRC_DIR}/hal/time/time.hpp
    ${COMMON_SRC_DIR}/hal/time/rtc.hpp
    ${COMMON_SRC_DIR}/hal/time/sleep.hpp
    ${COMMON_SRC_DIR}/hal/time/watchdog.hpp
    ${COMMON_SRC_DIR}/hal/utils/assert.hpp

    ${COMMON_SRC_DIR}/logger/logger.hpp
    ${COMMON_SRC_DIR}/timer/intervalTimer.hpp
    ${COMMON_SRC_DIR}/timer/timeoutTimer.hpp

    ${COMMON_SRC_DIR}/display/display.hpp
    ${COMMON_SRC_DIR}/display/font.hpp
    ${COMMON_SRC_DIR}/display/images.hpp
    ${COMMON_SRC_DIR}/display/colors.hpp

    ${COMMON_SRC_DIR}/timer/manager.hpp
    ${COMMON_SRC_DIR}/utils.hpp

    ${DRIVERS_SRC_DIR}/lcd/displayDriver.hpp
    ${DRIVERS_SRC_DIR}/lcd/pcd8544/displayPcd8544.hpp
    ${DRIVERS_SRC_DIR}/interfaces/onewire.hpp
    ${DRIVERS_SRC_DIR}/interfaces/onewireImpl.hpp
    ${DRIVERS_SRC_DIR}/devices/ds18b20.hpp

)

set(common_srcs

    # ${COMMON_SRC_DIR}/logger.cpp
    ${COMMON_SRC_DIR}/main.cpp
    ${COMMON_SRC_DIR}/logger/logger.cpp

    # ${COMMON_SRC_DIR}/stm32f10x_it.cpp
    # ${COMMON_SRC_DIR}/syscalls.cpp
    # ${COMMON_SRC_DIR}/system_stm32f10x.c
    # ${COMMON_SRC_DIR}/usart.cpp
    # ${COMMON_SRC_DIR}/utils.cpp
)

set(common_incs
    ${COMMON_SRC_DIR}/logger/logger.hpp
    # ${COMMON_SRC_DIR}/stm32f10x_conf.h
    # ${COMMON_SRC_DIR}/stm32f10x_it.hpp
    # ${COMMON_SRC_DIR}/stm32includes.hpp
    # ${COMMON_SRC_DIR}/syscall.hpp
    # ${COMMON_SRC_DIR}/a/types.hpp
    # ${COMMON_SRC_DIR}/usart.hpp
    # ${COMMON_SRC_DIR}/utils.hpp
)
