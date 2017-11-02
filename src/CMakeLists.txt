include(cmake/common_sources.cmake)

set(production_srcs ${common_porting_sources} ${common_porting_includes})
include_directories("${PROJECT_SOURCE_DIR}/src")

set(target_libs ${target_libs} gsl sml)# ArduinoJson sml crcpp gsl)
set(target_name AquaLampDriver)
set(target_name_lib Firmware)

if (${ARCH} STREQUAL "X86")
    include(cmake/x86_sources.cmake)
    find_package(Boost 1.58 COMPONENTS system program_options REQUIRED)
    include_directories(SYSTEM ${Boost_INCLUDE_DIR})
    include_directories(${PROJECT_SOURCE_DIR}/src/hal/x86)
    set(production_srcs ${production_srcs} ${x86_sources} ${x86_includes})
    set(target_libs ${target_libs} ${Boost_LIBRARIES} beast stdc++fs pthread)
    if (WIN32)
        set(target_libs ${target_libs} ws2_32 wsock32)
    elseif (UNIX)
        set(target_libs ${target_libs} pthread)
    endif (WIN32)
    add_executable(${target_name} ${production_srcs})
    target_link_libraries(${target_name} ${target_libs})
elseif (${ARCH} STREQUAL "STM32")
    include(cmake/stm32_sources.cmake)
    set(production_srcs ${production_srcs} ${stm32_sources} ${stm32_includes})
    include_directories(${PROJECT_SOURCE_DIR}/src/hal/stm32)

    include_directories(
        ${STM32_INCLUDE_DIRS}
        )

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD")

    if (DEBUG)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    endif (DEBUG)

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T${CMAKE_SOURCE_DIR}/lkr/stm32f103_128k.ld --specs=nano.specs")
    add_library(stm32lib ${STM32_SOURCES})
    add_executable(${target_name} ${production_srcs})
    message("prod ${production_srcs}")
    target_link_libraries(${target_name} stm32lib ${STM32_LIBRARIES} ${target_libs})

    install(TARGETS ${target_name} DESTINATION ${CMAKE_BINARY_DIR})
    add_custom_command(TARGET POST_BUILD ${target_name}
        COMMAND ${ARM_TOOLCHAIN}/bin/arm-none-eabi-size --format=berkeley "${target_name}.elf")

    add_custom_target(${target_name}.hex DEPENDS ${target_name} COMMAND ${CMAKE_OBJCOPY} -Oihex ${target_name}.elf ${target_name}.hex)
    file(TO_CMAKE_PATH "${CMAKE_OBJCOPY}" OBJCPY)
    message("command ${target_name}.bin DEPENDS ${target_name} COMMAND ${OBJCPY} -Obinary ${target_name}.elf ${target_name}.bin")

    add_custom_target(${target_name}.bin DEPENDS ${target_name} COMMAND ${OBJCPY} -Obinary ${target_name}.elf ${target_name}.bin)

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
