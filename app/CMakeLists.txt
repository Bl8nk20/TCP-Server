set(APP_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/server.c")

add_executable(${EXECUTABLE_NAME} ${APP_SOURCE})

target_link_libraries(
    ${EXECUTABLE_NAME}
    PRIVATE 
    CommandLib
    SeriveFactoryLib
    # hier weitere Libraries hinzufügen...
)


if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        ${EXECUTABLE_NAME}
        ENABLE
        ${ENABLE_WARNINGS}
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS})
endif()
