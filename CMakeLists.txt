# Copyright (c) 2024, inunix3.
# This file is distributed under the MIT license (https://opensource.org/license/mit/)

cmake_minimum_required(VERSION 3.11)

project(raypong VERSION 1.0.0 LANGUAGES C)

if (CMAKE_C_COMPILER_ID STREQUAL "Clang" AND CMAKE_C_COMPILER_FRONTEND_VARIANT STREQUAL "GNU")
    set(COMPILER "clang")
elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(COMPILER "gcc")
endif()

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if (COMPILER STREQUAL "gcc" OR COMPILER STREQUAL "clang")
    set(COMPILE_OPTIONS -Wall -Wextra)

    # if (NOT COMPILER STREQUAL "gcc")
        # Those flags may report too many warnings when using GCC
        set(COMPILE_OPTIONS ${COMPILE_OPTIONS} -Wshadow)
        set(COMPILE_OPTIONS ${COMPILE_OPTIONS} -Wconversion)
        set(COMPILE_OPTIONS ${COMPILE_OPTIONS} -Wsign-conversion)
    # endif()
endif()

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(ASSETS_DIR "${PROJECT_SOURCE_DIR}/assets")

set(HEADERS
    "${INCLUDE_DIR}/raypong/audio.h"
    "${INCLUDE_DIR}/raypong/ball.h"
    "${INCLUDE_DIR}/raypong/collision.h"
    "${INCLUDE_DIR}/raypong/defs.h"
    "${INCLUDE_DIR}/raypong/paddle.h"
    "${INCLUDE_DIR}/raypong/score.h"
    "${INCLUDE_DIR}/raypong/state.h"
    "${INCLUDE_DIR}/raypong/timer.h"
    "${INCLUDE_DIR}/raypong/ui.h"
    "${INCLUDE_DIR}/style_dark.h"
)

set(SOURCES
    "${SRC_DIR}/audio.c"
    "${SRC_DIR}/ball.c"
    "${SRC_DIR}/main.c"
    "${SRC_DIR}/paddle.c"
    "${SRC_DIR}/score.c"
    "${SRC_DIR}/state.c"
    "${SRC_DIR}/timer.c"
    "${SRC_DIR}/ui.c"
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib raygui)
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})

# Web Configurations
if ("${PLATFORM}" STREQUAL "Web")
    # Tell Emscripten to build an raypong.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

add_subdirectory(third-party)

# Taken from https://thatonegamedev.com/cpp/cmake/how-to-embed-files-in-your-c-project/
# Adapted for C, and changed the output filename format.
function(target_embed_files TARGET_NAME)
    set(OPTIONS)
    set(SINGLE_VALUE)
    set(MULTIPLE_VALUE FILES)

    cmake_parse_arguments(
        EF
        "${OPTIONS}"
        "${SINGLE_VALUE}"
        "${MULTIPLE_VALUE}"
        ${ARGN}
    )

    string(TOUPPER "${TARGET_NAME}" TARGET_NAME_UPPER)
    string(MAKE_C_IDENTIFIER "${TARGET_NAME_UPPER}" TARGET_NAME_UPPER)

    string(TOLOWER "${TARGET_NAME}" TARGET_NAME_LOWER)
    string(MAKE_C_IDENTIFIER "${TARGET_NAME_LOWER}" TARGET_NAME_LOWER)

    set(GENERATE_HEADER_LOCATION "${CMAKE_BINARY_DIR}/embed/include")
    set(EMBED_HEADERS_LOCATION "${GENERATE_HEADER_LOCATION}/embed")
    set(HEADER_FILENAME "${TARGET_NAME_LOWER}.h")
    set(ARRAY_DECLARATIONS)

    foreach(INPUT_FILE IN LISTS EF_FILES)
        get_filename_component(FILENAME "${INPUT_FILE}" NAME_WE)
        string(TOLOWER "${FILENAME}" FILENAME)
        string(MAKE_C_IDENTIFIER "${FILENAME}" FILENAME)

        file(READ "${INPUT_FILE}" BYTES HEX)
        string(REGEX REPLACE "(..)" "0x\\1, " BYTES "${BYTES}")

        string(CONFIGURE "static const unsigned char ef_${FILENAME}[] = { ${BYTES} }\;" CURRENT_DECLARATION)

        list(APPEND ARRAY_DECLARATIONS "${CURRENT_DECLARATION}")
    endforeach()

    string(JOIN "\n" ARRAY_DECLARATIONS ${ARRAY_DECLARATIONS})

    set(BASIC_HEADER "\
#pragma once

${ARRAY_DECLARATIONS}
    ")

    string(CONFIGURE "${BASIC_HEADER}" BASIC_HEADER)

    file(WRITE "${EMBED_HEADERS_LOCATION}/${HEADER_FILENAME}" "${BASIC_HEADER}")
    target_include_directories(${TARGET_NAME} PUBLIC "${GENERATE_HEADER_LOCATION}")
endfunction()

target_embed_files(
    ${PROJECT_NAME}
    FILES
    "${ASSETS_DIR}/goal.wav"
    "${ASSETS_DIR}/paddle_hit.wav"
    "${ASSETS_DIR}/wall_hit.wav"
    "${ASSETS_DIR}/main_menu_bg.png"
)
