set(
    LIBRARY_SOURCES_DUNGEON_GENERATOR
    "${CMAKE_CURRENT_SOURCE_DIR}/command.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/echo_command.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/uppercase_command.c"
)

set(
    LIBRARY_HEADERS_DUNGEON_GENERATOR
    "${CMAKE_CURRENT_SOURCE_DIR}/command.h"
)

add_library(
    "DungeonGeneratorLib"
    STATIC
    ${LIBRARY_SOURCES_COMMAND}
    ${LIBRARY_HEADERS_COMMAND}
)

target_include_directories(
    "DungeonGeneratorLib"
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/.."
)
