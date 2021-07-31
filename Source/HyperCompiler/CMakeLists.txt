#-------------------------------------------------------------------------------------------
# Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# CMake Info
#-------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.10)

#-------------------------------------------------------------------------------------------
# HyperCompiler
#-------------------------------------------------------------------------------------------
set(SOURCES
        src/main.cpp
        src/HyperCompiler/Compiler.cpp
        src/HyperCompiler/Lexer.cpp
        src/HyperCompiler/Logger.cpp
        src/HyperCompiler/Token.cpp
        src/HyperCompiler/Utils/Utilities.cpp)

set(HEADERS
        include/HyperCompiler/BuildOptions.hpp
        include/HyperCompiler/Compiler.hpp
        include/HyperCompiler/Lexer.hpp
        include/HyperCompiler/Logger.hpp
        include/HyperCompiler/Token.hpp
        include/HyperCompiler/Utils/Assertion.hpp
        include/HyperCompiler/Utils/PlatformDetection.hpp
        include/HyperCompiler/Utils/Prerequisites.hpp
        include/HyperCompiler/Utils/Utilities.hpp)

add_executable(HyperCompiler ${SOURCES} ${HEADERS})
target_include_directories(HyperCompiler PRIVATE include)
target_link_libraries(HyperCompiler PRIVATE ProjectOptions ProjectWarnings fmt llvm)

add_custom_command(
        TARGET HyperCompiler
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/tests ${CMAKE_CURRENT_BINARY_DIR}/tests)
