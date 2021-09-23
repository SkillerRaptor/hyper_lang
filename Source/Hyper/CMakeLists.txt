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
        src/Hyper/Token.cpp
        src/Hyper/Utils.cpp)

set(HEADERS
        include/Hyper/Lexer.hpp
        include/Hyper/Logger.hpp
        include/Hyper/Token.hpp
        include/Hyper/Utils.hpp)

hyperlang_define_executable(hyper)
target_link_libraries(
        hyper
        PRIVATE
        CONAN_PKG::fmt)
add_custom_command(
        TARGET hyper
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/tests $<TARGET_FILE_DIR:hyper>/tests)
