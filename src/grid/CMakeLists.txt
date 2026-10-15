set(
    LIBRARY_SOURCES_GRID
    "${CMAKE_CURRENT_SOURCE_DIR}/grid.c"
)

set(
    LIBRARY_HEADERS_GRID
    "${CMAKE_CURRENT_SOURCE_DIR}/grid.h"
)

add_library(
    "GridLib"
    STATIC
    ${LIBRARY_SOURCES_GRID}
    ${LIBRARY_HEADERS_GRID}
)

target_include_directories(
    "GridLib"
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/.."
)
