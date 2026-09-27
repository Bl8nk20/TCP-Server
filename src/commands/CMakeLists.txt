set(
    LIBRARY_SOURCES_COMMAND
    "${CMAKE_CURRENT_SOURCE_DIR}/command.c"
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

target_include_directories(
    "CommandLib"
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/.."
)

