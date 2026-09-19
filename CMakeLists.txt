cmake_minimum_required(VERSION 3.22)

project(
    "TCP-Server"
    VERSION 1.0.0
    LANGUAGES C CXX
)

option(ENABLE_WARNINGS "Enable to add Warnings to a target" ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable to treat warnings as errors" ON)

option(ENABLE_SANITIZE_ADDR "Enable address sanitize." OFF)
option(ENABLE_SANITIZE_UNDEF "Enable undefined sanitize." OFF)
option(ENABLE_SANITIZE_LEAK "Enable leak sanitize (Gcc/Clang only)." OFF)
option(ENABLE_SANITIZE_THREAD "Enable thread sanitize (Gcc/Clang only)." OFF)

set(EXECUTEABLE_NAME "server")

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

if(ENABLE_WARNINGS)
    include(Warnings)
endif()

if(ENABLE_SANITIZE_ADDR
   OR ENABLE_SANITIZE_UNDEF
   OR ENABLE_SANITIZE_LEAK
   OR ENABLE_SANITIZE_THREAD)
    include(Sanitizer)
    add_sanitizer_flags()
endif()

add_subdirectory(src)
add_subdirectory(app)

install(
    TARGETS ${EXECUTABLE_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

#install(
#    TARGETS
#    ARCHIVE DESTINATION lib
#    LIBRARY DESTINATION lib)
