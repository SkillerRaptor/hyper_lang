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
        src/Hyper/Lexer.cpp
        src/Hyper/Logger.cpp
        src/Hyper/Parser.cpp
        src/Hyper/Token.cpp
        src/Hyper/Utils.cpp)

set(HEADERS
        include/Hyper/Lexer.hpp
        include/Hyper/Logger.hpp
        include/Hyper/Parser.hpp
        include/Hyper/Token.hpp
        include/Hyper/Utils.hpp)

foreach (item IN ITEMS ${SOURCES} ${HEADERS})
    get_filename_component(src_path "${item}" PATH)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" group_path "${src_path}")
    string(REPLACE ".." "\\" group_path "${group_path}")
    source_group("${group_path}" FILES "${item}")
endforeach ()

add_executable(Hyper ${SOURCES} ${HEADERS})
target_link_libraries(Hyper
        PRIVATE
        ProjectOptions
        ProjectWarnings)
target_include_directories(
        Hyper
        PRIVATE
        include)
target_link_libraries(
        Hyper
        PRIVATE
        CONAN_PKG::fmt)
# add_custom_command(
#        TARGET hyper
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory tests $<TARGET_FILE_DIR:hyper>/tests)
