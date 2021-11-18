#-------------------------------------------------------------------------------------------
# Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
#
# SPDX-License-Identifier: MIT
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# LLVM
#-------------------------------------------------------------------------------------------
find_package(LLVM REQUIRED)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(LLVM_LINK_COMPONENTS
        AllTargetsAsmParsers
        AllTargetsDescs
        AllTargetsDisassemblers
        AllTargetsInfos
        AllTargetsCodeGens
        Analysis
        BitReader
        Core
        InstCombine
        MC
        MCDisassembler
        Object
        ScalarOpts
        Support
        Target
        TransformUtils
        native
        nativecodegen
        AsmPrinter
        Linker
        LTO
        WindowsManifest
        DebugInfoPDB
        LibDriver
        Option
        IrReader)

llvm_map_components_to_libnames(llvm_libs ${LLVM_LINK_COMPONENTS})

find_library(LLD_COFF NAMES lldCOFF.a liblldCOFF.a lldCOFF.lib PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_COMMON NAMES lldCommon.a liblldCommon.a lldCommon.lib PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_CORE NAMES lldCore.a liblldCore.a lldCore.lib PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_WASM NAMES lldWasm.a liblldWasm.a lldWasm.lib PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_MINGW NAMES lldMinGW.a liblldMinGW.a lldMinGW.lib PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_ELF NAMES lldELF.a liblldELF.a lldELF.lib PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_DRIVER NAMES lldDriver.a liblldDriver.a lldDriver.lib PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_READER_WRITER NAMES lldReaderWriter.a liblldReaderWriter.a lldReaderWriter.lib PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_MACHO NAMES lldMachO.a liblldMachO.a lldMachO.lib PATHS ${LLVM_LIBRARY_DIRS})
find_library(LLD_YAML NAMES lldYAML.a liblldYAML.a lldYAML.lib PATHS ${LLVM_LIBRARY_DIRS})

set(lld_libs
        ${LLD_COFF}
        ${LLD_COMMON}
        ${LLD_WASM}
        ${LLD_MINGW}
        ${LLD_ELF}
        ${LLD_DRIVER}
        ${LLD_READER_WRITER}
        ${LLD_MACHO}
        ${LLD_YAML}
        ${LLD_CORE})

add_library(llvm INTERFACE)
target_compile_definitions(
        llvm
        INTERFACE)
target_link_libraries(
        llvm
        INTERFACE)
target_include_directories(
        llvm
        INTERFACE)

#-------------------------------------------------------------------------------------------
# Hyper
#-------------------------------------------------------------------------------------------
set(SOURCES
        src/main.cpp
        src/Hyper/Compiler.cpp
        src/Hyper/DataType.cpp
        src/Hyper/Generator.cpp
        src/Hyper/Parser.cpp
        src/Hyper/Scanner.cpp
        src/Hyper/Token.cpp
        src/Hyper/Ast/AstFormatter.cpp
        src/Hyper/Ast/AstNode.cpp
        src/Hyper/Ast/Declarations/Declaration.cpp
        src/Hyper/Ast/Declarations/FunctionDeclaration.cpp
        src/Hyper/Ast/Declarations/TranslationUnitDeclaration.cpp
        src/Hyper/Ast/Declarations/VariableDeclaration.cpp
        src/Hyper/Ast/Expressions/BinaryExpression.cpp
        src/Hyper/Ast/Expressions/CallExpression.cpp
        src/Hyper/Ast/Expressions/Expression.cpp
        src/Hyper/Ast/Expressions/IdentifierExpression.cpp
        src/Hyper/Ast/Literals/Literal.cpp
        src/Hyper/Ast/Literals/NumericLiteral.cpp
        src/Hyper/Ast/Literals/StringLiteral.cpp
        src/Hyper/Ast/Statements/AssignStatement.cpp
        src/Hyper/Ast/Statements/CompoundStatement.cpp
        src/Hyper/Ast/Statements/ExpressionStatement.cpp
        src/Hyper/Ast/Statements/ForStatement.cpp
        src/Hyper/Ast/Statements/IfStatement.cpp
        src/Hyper/Ast/Statements/PrintStatement.cpp
        src/Hyper/Ast/Statements/ReturnStatement.cpp
        src/Hyper/Ast/Statements/Statement.cpp
        src/Hyper/Ast/Statements/WhileStatement.cpp)

set(HEADERS
        include/Hyper/Compiler.hpp
        include/Hyper/DataType.hpp
        include/Hyper/Generator.hpp
        include/Hyper/Formatter.hpp
        include/Hyper/Logger.hpp
        include/Hyper/Parser.hpp
        include/Hyper/Prerequisites.hpp
        include/Hyper/Scanner.hpp
        include/Hyper/Token.hpp
        include/Hyper/Ast/AstFormatter.hpp
        include/Hyper/Ast/AstNode.hpp
        include/Hyper/Ast/Forward.hpp
        include/Hyper/Ast/Declarations/Declaration.hpp
        include/Hyper/Ast/Declarations/FunctionDeclaration.hpp
        include/Hyper/Ast/Declarations/TranslationUnitDeclaration.hpp
        include/Hyper/Ast/Declarations/VariableDeclaration.hpp
        include/Hyper/Ast/Expressions/BinaryExpression.hpp
        include/Hyper/Ast/Expressions/CallExpression.hpp
        include/Hyper/Ast/Expressions/Expression.hpp
        include/Hyper/Ast/Expressions/IdentifierExpression.hpp
        include/Hyper/Ast/Literals/Literal.hpp
        include/Hyper/Ast/Literals/NumericLiteral.hpp
        include/Hyper/Ast/Literals/StringLiteral.hpp
        include/Hyper/Ast/Statements/AssignStatement.hpp
        include/Hyper/Ast/Statements/CompoundStatement.hpp
        include/Hyper/Ast/Statements/ExpressionStatement.hpp
        include/Hyper/Ast/Statements/ForStatement.hpp
        include/Hyper/Ast/Statements/IfStatement.hpp
        include/Hyper/Ast/Statements/PrintStatement.hpp
        include/Hyper/Ast/Statements/ReturnStatement.hpp
        include/Hyper/Ast/Statements/Statement.hpp
        include/Hyper/Ast/Statements/WhileStatement.hpp)

add_executable(hyper ${SOURCES} ${HEADERS})
target_compile_definitions(
        hyper
        PRIVATE
        ${LLVM_DEFINITIONS})
target_link_libraries(
        hyper
        PRIVATE
        ProjectOptions
        ProjectWarnings
        ${llvm_libs}
        ${lld_libs})
target_include_directories(
        hyper
        PRIVATE
        include
        ${LLVM_INCLUDE_DIRS})
add_custom_command(
        TARGET hyper
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/examples $<TARGET_FILE_DIR:hyper>/examples)
