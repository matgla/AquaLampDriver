include(cmake/common_sources.cmake)

set(production_srcs ${common_srcs} ${common_incs} main.cpp)
include_directories("${PROJECT_SOURCE_DIR}/src")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

set(target_libs ${target_libs} ArduinoJson sml crcpp gsl)
set(target_name AquaLampDriver)
set(target_name_lib Firmware)

if (${ARCH} STREQUAL "X86")
    message (FATAL_ERROR "Target for X86 is not currently supported")
elseif (${ARCH} STREQUAL "STM32")
    include_directories(
        ${CMAKE_SOURCE_DIR}/src
        ${STM32_INCLUDE_DIRS}
        )

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD")

    if(DEBUG)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -d -DUSE_FULL_ASSERT")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -d -DUSE_FULL_ASSERT")
    endif (DEBUG)

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T${CMAKE_SOURCE_DIR}/lkr/stm32f103_128k.ld --specs=nano.specs")

    add_library(stm32lib ${STM32_SOURCES} ${STM32_STARTUP_SOURCE})

    add_executable(${target_name} ${production_srcs})
    target_link_libraries(${target_name} stm32lib ${STM32_LIBRARIES} ${target_libs})

    add_custom_command(TARGET  POST_BUILD ${target_name}
        COMMAND ${ARM_TOOLCHAIN}/bin/arm-none-eabi-size --format=berkeley "${target_name}.elf")

    add_custom_target(${target_name}.hex DEPENDS ${target_name} COMMAND ${CMAKE_OBJCOPY} -Oihex ${target_name} ${target_name}.hex)
    add_custom_target(${target_name}.bin DEPENDS ${target_name} COMMAND ${CMAKE_OBJCOPY} -Obinary ${target_name} ${target_name}.bin)

    # If STM32 ST-Link Utility is found, add a make target to program the chip
    if(DEFINED STM32_STLINK_CLI_EXECUTABLE)
        # -c SWD UR : SWD communication protocol, Under Reset
        # -Q : quiet mode, no progress bar
        # -V : Verifies that the programming operation was performed successfully.
        # -P : program file (.hex)
        set(STLINK_CMD ${STM32_STLINK_CLI_EXECUTABLE} -c SWD UR -P ${CMAKE_BINARY_DIR}/${target_name}.hex)
        add_custom_target(program-flash DEPENDS ${target_name}.hex COMMAND ${STLINK_CMD})
    endif()
endif (${ARCH} STREQUAL "X86")
