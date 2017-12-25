set(PRODUCTION_SOURCES_DIR "${PROJECT_SOURCE_DIR}/src")
set(HAL_SOURCES_DIR "${PROJECT_SOURCE_DIR}/src/hal")

set(production_includes
    ${PRODUCTION_SOURCES_DIR}/app/context.hpp
    ${PRODUCTION_SOURCES_DIR}/app/settings/timeEventSettings.hpp
    ${PRODUCTION_SOURCES_DIR}/app/settings/channelsSettings.hpp
    ${PRODUCTION_SOURCES_DIR}/controller/channelController.hpp
    ${PRODUCTION_SOURCES_DIR}/containers/staticVector.hpp
    ${PRODUCTION_SOURCES_DIR}/display/font.hpp
    ${PRODUCTION_SOURCES_DIR}/display/display.hpp
    ${PRODUCTION_SOURCES_DIR}/logger/logger.hpp
    ${PRODUCTION_SOURCES_DIR}/logger/loggerConf.hpp
    ${PRODUCTION_SOURCES_DIR}/timer/intervalTimer.hpp
    ${PRODUCTION_SOURCES_DIR}/timer/timeoutTimer.hpp
    ${PRODUCTION_SOURCES_DIR}/timer/manager.hpp
    ${PRODUCTION_SOURCES_DIR}/utils.hpp
    ${PRODUCTION_SOURCES_DIR}/utils/constants.hpp
    ${PRODUCTION_SOURCES_DIR}/controller/sunlightController.hpp

    ${HAL_SOURCES_DIR}/core/criticalSection.hpp
    ${HAL_SOURCES_DIR}/core/core.hpp
    ${HAL_SOURCES_DIR}/core/backupRegisters.hpp
    ${HAL_SOURCES_DIR}/utils/assert.hpp
    ${HAL_SOURCES_DIR}/memory/eeprom.hpp
    ${HAL_SOURCES_DIR}/time/sleep.hpp
    ${HAL_SOURCES_DIR}/time/time.hpp
    ${HAL_SOURCES_DIR}/time/rtc.hpp

)

set(production_sources
    ${production_includes}
    ${PRODUCTION_SOURCES_DIR}/app/context.cpp
    ${PRODUCTION_SOURCES_DIR}/app/settings/timeEventSettings.cpp
    ${PRODUCTION_SOURCES_DIR}/app/settings/channelsSettings.cpp
    ${PRODUCTION_SOURCES_DIR}/controller/channelController.cpp
    
    ${PRODUCTION_SOURCES_DIR}/display/font.cpp
    ${PRODUCTION_SOURCES_DIR}/display/display.cpp
    
    ${PRODUCTION_SOURCES_DIR}/logger/logger.cpp
    ${PRODUCTION_SOURCES_DIR}/logger/loggerConf.cpp    
    ${PRODUCTION_SOURCES_DIR}/utils.cpp
    ${PRODUCTION_SOURCES_DIR}/timer/intervalTimer.cpp
    ${PRODUCTION_SOURCES_DIR}/timer/timeoutTimer.cpp
    ${PRODUCTION_SOURCES_DIR}/controller/sunlightController.cpp
    

    ${HAL_SOURCES_DIR}/x86/core/criticalSection_x86.cpp
    ${HAL_SOURCES_DIR}/x86/core/core_x86.cpp
    ${HAL_SOURCES_DIR}/x86/core/backupRegisters_x86.cpp
    ${HAL_SOURCES_DIR}/x86/utils/assert_x86.cpp
    ${HAL_SOURCES_DIR}/x86/memory/eeprom_x86.cpp
    ${HAL_SOURCES_DIR}/x86/time/sleep_x86.cpp
    ${HAL_SOURCES_DIR}/x86/time/time_x86.cpp
    ${HAL_SOURCES_DIR}/x86/time/rtc_x86.cpp
)
