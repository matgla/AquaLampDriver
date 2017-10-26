set(COMMON_SRC_DIR "${PROJECT_SOURCE_DIR}/src")

set(stm32_sources
    ${COMMON_SRC_DIR}/stm32f10x_it.cpp
    ${COMMON_SRC_DIR}/stm32f10x_it.cpp
    ${COMMON_SRC_DIR}/system_stm32f10x.c

    ${COMMON_SRC_DIR}/syscalls.cpp
    ${COMMON_SRC_DIR}/rtc/rtc.cpp

)

set(stm32_includes
    ${COMMON_SRC_DIR}/stm32f10x_conf.h
    ${COMMON_SRC_DIR}/stm32f10x_it.hpp
    ${COMMON_SRC_DIR}/syscall.hpp
    ${COMMON_SRC_DIR}/rtc/rtc.hpp
)
