set(
    LIBRARY_SOURCES_SHARED
    "${CMAKE_CURRENT_SOURCE_DIR}/shared.c"
)

set(
    LIBRARY_HEADERS_SHARED 
    "${CMAKE_CURRENT_SOURCE_DIR}/shared.h"
)

add_library(
    "SharedLib"
    STATIC
    ${LIBRARY_SOURCES_SHARED}
    ${LIBRARY_HEADERS_SHARED}
)

target_include_directories(
    "SharedLib"
    PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/..")
