if (${ARCH} STREQUAL "X86")
    add_subdirectory(beast)
endif (${ARCH} STREQUAL "X86")

add_subdirectory(json)
add_subdirectory(boost)
add_subdirectory(CRCpp)
add_subdirectory(gsl)
