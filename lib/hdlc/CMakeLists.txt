file(GLOB_RECURSE hdlc_includes
    "hdlc/*.h"
    "hdlc/*.hpp"
)

file(GLOB_RECURSE hdlc_srcs
    "hdlc/*.c"
    "hdlc/*.cpp"
)

set(HDLC_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/lib/hdlc" CACHE STRING "path to HDLC sources" FORCE)
add_library(hdlc STATIC ${hdlc_includes} ${hdlc_srcs})
target_include_directories(hdlc PUBLIC ${HDLC_INCLUDE_DIR})
