set(COMMON_SRC_DIR "${PROJECT_SOURCE_DIR}/src")

set(common_porting_sources
    ${COMMON_SRC_DIR}/app.cpp
    ${COMMON_SRC_DIR}/main.cpp
    ${COMMON_SRC_DIR}/logger/logger.cpp
    ${COMMON_SRC_DIR}/timer/intervalTimer.cpp
    ${COMMON_SRC_DIR}/timer/manager.cpp
    ${COMMON_SRC_DIR}/timer/timeoutTimer.cpp

    #${COMMON_SRC_DIR}/usart.cpp
    #${COMMON_SRC_DIR}/utils.cpp
    #${COMMON_SRC_DIR}/dispatcher/ChannelHandler.cpp
    #${COMMON_SRC_DIR}/dispatcher/dispatcher.cpp
    #${COMMON_SRC_DIR}/dispatcher/handlerBase.cpp
    #${COMMON_SRC_DIR}/dispatcher/RtcHandler.cpp
    #${COMMON_SRC_DIR}/pwm/channelsGroup.cpp
    # ${COMMON_SRC_DIR}/pwmChannel.cpp
    # ${COMMON_SRC_DIR}/logger.cpp

)

set(common_porting_includes
    ${COMMON_SRC_DIR}/app.hpp

    ${COMMON_SRC_DIR}/hal/core/core.hpp    
    ${COMMON_SRC_DIR}/hal/core/backupRegisters.hpp    
    ${COMMON_SRC_DIR}/hal/time/time.hpp
    ${COMMON_SRC_DIR}/hal/time/rtc.hpp
    ${COMMON_SRC_DIR}/hal/time/sleep.hpp  

    ${COMMON_SRC_DIR}/logger/logger.hpp
    ${COMMON_SRC_DIR}/timer/IManager.hpp
    ${COMMON_SRC_DIR}/timer/intervalTimer.hpp
    ${COMMON_SRC_DIR}/timer/ITimer.hpp
    ${COMMON_SRC_DIR}/timer/manager.hpp
    ${COMMON_SRC_DIR}/timer/timeoutTimer.hpp


    # ${COMMON_SRC_DIR}/usart.hpp
    # ${COMMON_SRC_DIR}/utils.hpp
    # ${COMMON_SRC_DIR}/dispatcher/ChannelHandler.hpp
    # ${COMMON_SRC_DIR}/dispatcher/dispatcher.hpp
    # ${COMMON_SRC_DIR}/dispatcher/fwd.hpp
    # ${COMMON_SRC_DIR}/dispatcher/handlerBase.hpp
    # ${COMMON_SRC_DIR}/dispatcher/IHandler.hpp
    # ${COMMON_SRC_DIR}/dispatcher/RtcHandler.hpp
    # ${COMMON_SRC_DIR}/pwm/channelsGroup.hpp
    # ${COMMON_SRC_DIR}/rtc/rtc.hpp
    # ${COMMON_SRC_DIR}/state_machine/bootloader_sm.hpp
    # ${COMMON_SRC_DIR}/state_machine/helpers.hpp
    # ${COMMON_SRC_DIR}/buffer.hpp
    # ${COMMON_SRC_DIR}/memoryHelpers.hpp
    # ${COMMON_SRC_DIR}/pwmChannel.hpp
    # ${COMMON_SRC_DIR}/readerWriterBuffer.hpp

    # ${COMMON_SRC_DIR}/logger/logger.hpp
    # ${COMMON_SRC_DIR}/app.hpp


    # ${COMMON_SRC_DIR}/hal/core/core.hpp    
    # ${COMMON_SRC_DIR}/hal/core/backupRegisters.hpp    
    # ${COMMON_SRC_DIR}/hal/time/time.hpp
    # ${COMMON_SRC_DIR}/hal/time/sleep.hpp    
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
