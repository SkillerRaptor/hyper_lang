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
        src/HyperCompiler/LLVMGenerator.cpp
        src/HyperCompiler/Logger.cpp
        src/HyperCompiler/Parser.cpp
        src/HyperCompiler/Token.cpp
        src/HyperCompiler/Ast/AstNode.cpp
        src/HyperCompiler/Ast/Declarations.cpp
        src/HyperCompiler/Ast/Expressions.cpp
        src/HyperCompiler/Ast/Literals.cpp
        src/HyperCompiler/Ast/Statements.cpp
        src/HyperCompiler/Ast/Value.cpp
        src/HyperCompiler/Utils/Utilities.cpp)

set(HEADERS
        include/HyperCompiler/BuildOptions.hpp
        include/HyperCompiler/Compiler.hpp
        include/HyperCompiler/Lexer.hpp
        include/HyperCompiler/LLVMGenerator.hpp
        include/HyperCompiler/Logger.hpp
        include/HyperCompiler/Parser.hpp
        include/HyperCompiler/Token.hpp
        include/HyperCompiler/Ast/AstNode.hpp
        include/HyperCompiler/Ast/Declarations.hpp
        include/HyperCompiler/Ast/Expressions.hpp
        include/HyperCompiler/Ast/Statements.hpp
        include/HyperCompiler/Ast/Literals.hpp
        include/HyperCompiler/Ast/Value.hpp
        include/HyperCompiler/Utils/Assertion.hpp
        include/HyperCompiler/Utils/PlatformDetection.hpp
        include/HyperCompiler/Utils/Prerequisites.hpp
        include/HyperCompiler/Utils/Utilities.hpp)

if ($ENV{CLION_IDE})
    # TODO: FIX ME
    include_directories("/usr/include/llvm-10/")
    include_directories("/usr/include/llvm-c-10/")
endif ()

find_package(LLVM REQUIRED CONFIG)

add_library(HyperLinker STATIC src/HyperCompiler/Linker.cpp include/HyperCompiler/Linker.hpp)
target_compile_definitions(HyperLinker PRIVATE ${LLVM_DEFS})
target_include_directories(HyperLinker PRIVATE ${LLVM_INCLUDE} include)
target_link_libraries(HyperLinker PRIVATE ProjectOptions ProjectWarnings fmt ${LLVM_LIBS} ${LLD_LIBS})

add_executable(HyperCompiler ${SOURCES} ${HEADERS})
target_compile_definitions(HyperCompiler PRIVATE ${LLVM_DEFS})
target_include_directories(HyperCompiler PRIVATE ${LLVM_INCLUDE} include)
target_link_libraries(HyperCompiler PRIVATE ProjectOptions ProjectWarnings fmt ${LLVM_LIBS} HyperLinker ${LLD_LIBS})

add_custom_command(
        TARGET HyperCompiler
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/tests ${CMAKE_CURRENT_BINARY_DIR}/tests)
