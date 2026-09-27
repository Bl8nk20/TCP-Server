set(LIBRARY_HEADERS_SERVICE_FACTORY 
    "${CMAKE_CURRENT_SOURCE_DIR}/services.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/factory.h")

set(LIBRARY_SOURCES_SERVICE_FACTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/factory.c"
)

add_library(
    "ServiceFactoryLib" 
    STATIC
    ${LIBRARY_SOURCES_SERVICE_FACTORY}
    ${LIBRARY_HEADERS_SERVICE_FACTORY}
)

target_link_libraries(
    "ServiceFactoryLib"
    PRIVATE 
    CommandLib
)

target_include_directories(
    "ServiceFactoryLib"
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/.."
)
