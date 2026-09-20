function(target_set_warnings)
    set(oneValueArgs TARGET ENABLE AS_ERRORS)

    cmake_parse_arguments(
        TARGET_SET_WARNINGS
        ""
        "${oneValueArgs}"
        ""
        ${ARGN}
    )

    if(NOT TARGET_SET_WARNINGS_ENABLE)
        message(STATUS "Warnings Disabled for: ${TARGET_SET_WARNINGS_TARGET}")
        return()
    endif()

    message(STATUS "Warnings Active for: ${TARGET_SET_WARNINGS_TARGET}")
    message(STATUS "Warnings as Errors: ${TARGET_SET_WARNINGS_AS_ERRORS}")

    set(MSVC_WARNINGS
        /W4
        /permissive-
        /w14242
        /w14254
        /w14287
        /w14296
        /w14311
        /w44062
        /w44242
        /w14826
        /w14905
        /w14906
        /w14263
        /w14265
        /w14640
        /w14928
        /we4289
    )

    set(CLANG_WARNINGS
        -Wall
        -Wextra
        -Wshadow
        -Wpedantic
        -Wunused
        -Wformat=2
        -Wcast-align
        -Wconversion
        -Wsign-conversion
        -Wnull-dereference
        -Wdouble-promotion
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Woverloaded-virtual
        -Weffc++
    )

    set(GCC_WARNINGS
        ${CLANG_WARNINGS}
        -Wduplicated-cond
        -Wduplicated-branches
        -Wlogical-op
    )

    if(TARGET_SET_WARNINGS_AS_ERRORS)
        list(APPEND CLANG_WARNINGS -Werror)
        list(APPEND GCC_WARNINGS -Werror)
        list(APPEND MSVC_WARNINGS /WX)
    endif()

    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(WARNINGS ${MSVC_WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(WARNINGS ${CLANG_WARNINGS})
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(WARNINGS ${GCC_WARNINGS})
    else()
        message(WARNING
            "Unknown compiler: ${CMAKE_CXX_COMPILER_ID}. "
            "No warning flags configured."
        )
        return()
    endif()

    target_compile_options(
        ${TARGET_SET_WARNINGS_TARGET}
        PRIVATE
        ${WARNINGS}
    )
endfunction()
