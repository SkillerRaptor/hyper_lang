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
        src/Hyper/Diagnostics.cpp
        src/Hyper/Lexer.cpp
        src/Hyper/Parser.cpp
        src/Hyper/Validator.cpp
        src/Hyper/Validators/ScopeValidator.cpp
        src/Hyper/Validators/TypeValidator.cpp
        src/Hyper/Ast/AstNode.cpp
        src/Hyper/Ast/Declaration.cpp
        src/Hyper/Ast/Expression.cpp
        src/Hyper/Ast/Literal.cpp
        src/Hyper/Ast/Statement.cpp
        src/Hyper/Ast/Declarations/FunctionDeclaration.cpp
        src/Hyper/Ast/Declarations/TranslationUnitDeclaration.cpp
        src/Hyper/Ast/Declarations/VariableDeclaration.cpp
        src/Hyper/Ast/Expressions/BinaryExpression.cpp
        src/Hyper/Ast/Expressions/CallExpression.cpp
        src/Hyper/Ast/Expressions/CastExpression.cpp
        src/Hyper/Ast/Expressions/ConditionalExpression.cpp
        src/Hyper/Ast/Expressions/IdentifierExpression.cpp
        src/Hyper/Ast/Expressions/UnaryExpression.cpp
        src/Hyper/Ast/Literals/BoolLiteral.cpp
        src/Hyper/Ast/Literals/IntegerLiteral.cpp
        src/Hyper/Ast/Literals/StringLiteral.cpp
        src/Hyper/Ast/Statements/AssignStatement.cpp
        src/Hyper/Ast/Statements/CompoundStatement.cpp
        src/Hyper/Ast/Statements/ExpressionStatement.cpp
        src/Hyper/Ast/Statements/IfStatement.cpp
        src/Hyper/Ast/Statements/CompoundAssignStatement.cpp
        src/Hyper/Ast/Statements/ReturnStatement.cpp
        src/Hyper/Ast/Statements/WhileStatement.cpp)

set(HEADERS
        include/Hyper/Compiler.hpp
        include/Hyper/Diagnostics.hpp
        include/Hyper/Formatter.hpp
        include/Hyper/Identifier.hpp
        include/Hyper/Lexer.hpp
        include/Hyper/Logger.hpp
        include/Hyper/Parser.hpp
        include/Hyper/SourceRange.hpp
        include/Hyper/Symbol.hpp
        include/Hyper/Token.hpp
        include/Hyper/Type.hpp
        include/Hyper/Validator.hpp
        include/Hyper/Validators/ScopeValidator.hpp
        include/Hyper/Validators/TypeValidator.hpp
        include/Hyper/Ast/AstNode.hpp
        include/Hyper/Ast/Declaration.hpp
        include/Hyper/Ast/Expression.hpp
        include/Hyper/Ast/Forward.hpp
        include/Hyper/Ast/Literal.hpp
        include/Hyper/Ast/Statement.hpp
        include/Hyper/Ast/Declarations/FunctionDeclaration.hpp
        include/Hyper/Ast/Declarations/TranslationUnitDeclaration.hpp
        include/Hyper/Ast/Declarations/VariableDeclaration.hpp
        include/Hyper/Ast/Expressions/BinaryExpression.hpp
        include/Hyper/Ast/Expressions/CallExpression.hpp
        include/Hyper/Ast/Expressions/CastExpression.hpp
        include/Hyper/Ast/Expressions/ConditionalExpression.hpp
        include/Hyper/Ast/Expressions/IdentifierExpression.hpp
        include/Hyper/Ast/Expressions/UnaryExpression.hpp
        include/Hyper/Ast/Literals/BoolLiteral.hpp
        include/Hyper/Ast/Literals/IntegerLiteral.hpp
        include/Hyper/Ast/Literals/StringLiteral.hpp
        include/Hyper/Ast/Statements/AssignStatement.hpp
        include/Hyper/Ast/Statements/CompoundStatement.hpp
        include/Hyper/Ast/Statements/ExpressionStatement.hpp
        include/Hyper/Ast/Statements/IfStatement.hpp
        include/Hyper/Ast/Statements/CompoundAssignStatement.hpp
        include/Hyper/Ast/Statements/ReturnStatement.hpp
        include/Hyper/Ast/Statements/WhileStatement.hpp)

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
