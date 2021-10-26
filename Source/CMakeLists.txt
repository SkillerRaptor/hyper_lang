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
        src/Hyper/Lexer.cpp
        src/Hyper/SourceLocation.cpp
        src/Hyper/Token.cpp)

set(HEADERS
        include/Hyper/Compiler.hpp
        include/Hyper/Lexer.hpp
        include/Hyper/SourceLocation.hpp
        include/Hyper/Token.hpp)

foreach (item IN ITEMS ${SOURCES} ${HEADERS})
    get_filename_component(src_path "${item}" PATH)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" group_path "${src_path}")
    string(REPLACE ".." "\\" group_path "${group_path}")
    source_group("${group_path}" FILES "${item}")
endforeach ()

add_executable(hyper ${SOURCES} ${HEADERS})
target_link_libraries(hyper
        PRIVATE
        ProjectOptions
        ProjectWarnings)
target_include_directories(
        hyper
        PRIVATE
        include)
add_custom_command(
        TARGET hyper
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/examples $<TARGET_FILE_DIR:hyper>/examples)
