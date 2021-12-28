#-------------------------------------------------------------------------------------------
# Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# Hyper
#-------------------------------------------------------------------------------------------
set(SOURCES
        src/main.cpp
        src/Hyper/Compiler.cpp
        src/Hyper/Lexer.cpp)

set(HEADERS
        include/Hyper/Compiler.hpp
        include/Hyper/Formatter.hpp
        include/Hyper/Lexer.hpp
        include/Hyper/Logger.hpp
        include/Hyper/Token.hpp)

add_executable(hyper ${SOURCES} ${HEADERS})
target_link_libraries(
        hyper
        PRIVATE
        ProjectOptions
        ProjectWarnings)
target_include_directories(
        hyper
        PUBLIC
        include)

add_custom_command(
        TARGET hyper
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/tests $<TARGET_FILE_DIR:hyper>/tests)
