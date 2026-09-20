set(
    LIBRARY_SOURCES_COMMAND 
    "${CMAKE_CURRENT_SOURCE_DIR}/echo_command.c" 
    "${CMAKE_CURRENT_SOURCE_DIR}/uppercase_command.c"
)

set(
    LIBRARY_HEADERS_COMMAND
    "${CMAKE_CURRENT_SOURCE_DIR}/command.h"
)

add_library(
    "CommandLib"
    STATIC
    ${LIBRARY_SOURCES_COMMAND}
    ${LIBRARY_HEADERS_COMMAND}
)


if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "CommandLib"
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

