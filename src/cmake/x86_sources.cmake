set(X86_SRC_DIR "${PROJECT_SOURCE_DIR}/src/hal/x86")
set(DRIVERS_SRC_DIR "${PROJECT_SOURCE_DIR}/src/drivers")

set(x86_sources
     ${X86_SRC_DIR}/serial/serial_x86.cpp
     ${X86_SRC_DIR}/core/backupRegisters_x86.cpp
     ${X86_SRC_DIR}/core/core_x86.cpp
     ${X86_SRC_DIR}/core/criticalSection_x86.cpp
     ${X86_SRC_DIR}/time/time_x86.cpp
     ${X86_SRC_DIR}/time/rtc_x86.cpp
     ${X86_SRC_DIR}/time/sleep_x86.cpp
     ${X86_SRC_DIR}/utils/assert_x86.cpp
     ${DRIVERS_SRC_DIR}/lcd/sfml/displaySfml.cpp          
)  
 
set(x86_includes
     ${X86_SRC_DIR}/config.hpp
     ${DRIVERS_SRC_DIR}/lcd/sfml/displaySfml.hpp     
)
