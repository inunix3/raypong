# Copyright (c) 2023-present, inunix3.
# This file is distributed under the MIT license (https://opensource.org/license/mit/)

add_subdirectory(raylib)

add_library(raygui INTERFACE raygui.h)
target_include_directories(raygui INTERFACE .)
