set(CMAKE_SYSTEM_NAME      STM32)
set(CMAKE_SYSTEM_VERSION   1)
set(CMAKE_SYSTEM_PROCESSOR arm-eabi)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

file(TO_CMAKE_PATH $ENV{ARM_TOOLCHAIN} ARM_TOOLCHAIN_PATH_CONVERTED)
set(ARM_TOOLCHAIN_PATH ${ARM_TOOLCHAIN_PATH_CONVERTED} CACHE PATH "Path to ARM toolchain" FORCE)
message("-- ARM toolchain: ${ARM_TOOLCHAIN_PATH_CONVERTED}")

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

set(CMAKE_ASM_COMPILER  "${ARM_TOOLCHAIN_PATH}/bin/arm-none-eabi-gcc")
set(CMAKE_C_COMPILER    "${ARM_TOOLCHAIN_PATH}/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER  "${ARM_TOOLCHAIN_PATH}/bin/arm-none-eabi-g++")
set(CMAKE_OBJCOPY       "${ARM_TOOLCHAIN_PATH}/bin/arm-none-eabi-objcopy")
set(CMAKE_OBJDUMP       "${ARM_TOOLCHAIN_PATH}/bin/arm-none-eabi-objdump")

set(TOOCHAIN_LIB_DIR "${ARM_TOOLCHAIN}/lib")

SET(CMAKE_C_FLAGS "-mthumb -mcpu=cortex-m4 -fno-builtin -Wall -std=gnu99 -fdata-sections -ffunction-sections -mfloat-abi=soft -s -Os" CACHE INTERNAL "c compiler flags")
SET(CMAKE_CXX_FLAGS "-mthumb -mcpu=cortex-m4 -fno-builtin -Wall -std=c++1y -fdata-sections -ffunction-sections -fno-builtin -mfloat-abi=soft -fno-rtti -fno-exceptions -fno-threadsafe-statics -Os" CACHE INTERNAL "cxx compiler flags")
SET(CMAKE_ASM_FLAGS "-mthumb -mcpu=cortex-m4" CACHE INTERNAL "asm compiler flags")

SET(CMAKE_EXE_LINKER_FLAGS "-nostartfiles -Wl,--gc-sections -mthumb -mcpu=cortex-m4 -flto " CACHE INTERNAL "exe link flags")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
