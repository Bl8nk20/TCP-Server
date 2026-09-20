set(LIBRARY_HEADERS_SERVICE_FACTORY "${CMAKE_CURRENT_SOURCE_DIR}/services.h" "${CMAKE_CURRENT_SOURCE_DIR}/factory.h")

add_library(
    "ServiceFactoryLib" 
    INTERFACE
    ${LIBRARY_HEADERS_SERVICE_FACTORY}
)

target_link_libraries(
    "ServiceFactoryLib"
    INTERFACE 
    CommandLib
)
