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
message(STATUS "Libraries located in: ${LLVM_LIBRARY_DIRS}")

set(LLVM_LINK_COMPONENTS
        AllTargetsAsmParsers
        AllTargetsCodeGens
        AllTargetsDescs
        AllTargetsDisassemblers
        AllTargetsInfos
        Analysis
        AsmPrinter
        BitReader
        Core
        DebugInfoPDB
        InstCombine
        IrReader
        LibDriver
        Linker
        LTO
        MC
        MCDisassembler
        native
        nativecodegen
        Object
        Option
        ScalarOpts
        Support
        Target
        TransformUtils
        WindowsManifest)

llvm_map_components_to_libnames(llvm_libs ${LLVM_LINK_COMPONENTS})

#-------------------------------------------------------------------------------------------
# Hyper
#-------------------------------------------------------------------------------------------
set(SOURCES
        src/main.cpp
        src/Hyper/Compiler.cpp
        src/Hyper/DataType.cpp
        src/Hyper/Diagnostics.cpp
        src/Hyper/Generator.cpp
        src/Hyper/Linker.cpp
        src/Hyper/LinkerFinder.cpp
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
        include/Hyper/Diagnostics.hpp
        include/Hyper/Formatter.hpp
        include/Hyper/Generator.hpp
        include/Hyper/Linker.hpp
        include/Hyper/LinkerFinder.hpp
        include/Hyper/Logger.hpp
        include/Hyper/Parser.hpp
        include/Hyper/Prerequisites.hpp
        include/Hyper/Scanner.hpp
        include/Hyper/Target.hpp
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
        ${llvm_libs})
target_include_directories(
        hyper
        PRIVATE
        include
        ${LLVM_INCLUDE_DIRS})
add_custom_command(
        TARGET hyper
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/examples $<TARGET_FILE_DIR:hyper>/examples)
