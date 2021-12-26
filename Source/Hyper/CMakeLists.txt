#-------------------------------------------------------------------------------------------
# Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# Hyper
#-------------------------------------------------------------------------------------------
set(SOURCES
        src/main.cpp)

set(HEADERS
        )

add_executable(Hyper ${SOURCES} ${HEADERS})
target_link_libraries(
        Hyper
        PRIVATE
        ProjectOptions
        ProjectWarnings)
target_include_directories(
        Hyper
        PUBLIC
        include)
