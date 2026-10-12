set(
    LIBRARY_SOURCES_DUNGEON_GENERATOR
    "${CMAKE_CURRENT_SOURCE_DIR}/generator.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/cellular_automata.c"
)

set(
    LIBRARY_HEADERS_DUNGEON_GENERATOR
    "${CMAKE_CURRENT_SOURCE_DIR}/generator.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/cellular_automata.h"
)

add_library(
    "DungeonGeneratorLib"
    STATIC
    ${LIBRARY_SOURCES_DUNGEON_GENERATOR}
    ${LIBRARY_HEADERS_DUNGEON_GENERATOR}
)

target_include_directories(
    "DungeonGeneratorLib"
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/.."
)
