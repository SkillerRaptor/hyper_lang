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
        src/Hyper/Parser.cpp
        src/Hyper/Scanner.cpp
        src/Hyper/Types.cpp
        src/Hyper/Ast/AstNode.cpp
        src/Hyper/Ast/Declarations/FunctionDeclaration.cpp
        src/Hyper/Ast/Declarations/VariableDeclaration.cpp
        src/Hyper/Ast/Expressions/BinaryExpression.cpp
        src/Hyper/Ast/Expressions/CallExpression.cpp
        src/Hyper/Ast/Expressions/IdentifierExpression.cpp
        src/Hyper/Ast/Literals/NumericLiteral.cpp
        src/Hyper/Ast/Statements/AssignStatement.cpp
        src/Hyper/Ast/Statements/CompoundStatement.cpp
        src/Hyper/Ast/Statements/ForStatement.cpp
        src/Hyper/Ast/Statements/IfStatement.cpp
        src/Hyper/Ast/Statements/PrintStatement.cpp
        src/Hyper/Ast/Statements/ReturnStatement.cpp
        src/Hyper/Ast/Statements/WhileStatement.cpp
        src/Hyper/Generators/CGenerator.cpp
        src/Hyper/Generators/Generator.cpp)

set(HEADERS
        include/Hyper/Parser.hpp
        include/Hyper/Scanner.hpp
        include/Hyper/SourceLocation.hpp
        include/Hyper/Token.hpp
        include/Hyper/Types.hpp
        include/Hyper/Ast/AstNode.hpp
        include/Hyper/Ast/Declarations/Declaration.hpp
        include/Hyper/Ast/Declarations/FunctionDeclaration.hpp
        include/Hyper/Ast/Declarations/VariableDeclaration.hpp
        include/Hyper/Ast/Expressions/BinaryExpression.hpp
        include/Hyper/Ast/Expressions/CallExpression.hpp
        include/Hyper/Ast/Expressions/Expression.hpp
        include/Hyper/Ast/Expressions/IdentifierExpression.hpp
        include/Hyper/Ast/Literals/NumericLiteral.hpp
        include/Hyper/Ast/Literals/Literal.hpp
        include/Hyper/Ast/Statements/AssignStatement.hpp
        include/Hyper/Ast/Statements/CompoundStatement.hpp
        include/Hyper/Ast/Statements/ForStatement.hpp
        include/Hyper/Ast/Statements/IfStatement.hpp
        include/Hyper/Ast/Statements/PrintStatement.hpp
        include/Hyper/Ast/Statements/ReturnStatement.hpp
        include/Hyper/Ast/Statements/Statement.hpp
        include/Hyper/Ast/Statements/WhileStatement.hpp
        include/Hyper/Generators/CGenerator.hpp
        include/Hyper/Generators/Generator.hpp)

foreach (item IN ITEMS ${SOURCES} ${HEADERS})
    get_filename_component(src_path "${item}" PATH)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" group_path "${src_path}")
    string(REPLACE ".." "\\" group_path "${group_path}")
    source_group("${group_path}" FILES "${item}")
endforeach ()

add_executable(hyper ${SOURCES} ${HEADERS})
target_compile_definitions(
        hyper
        PRIVATE)
target_link_libraries(
        hyper
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
