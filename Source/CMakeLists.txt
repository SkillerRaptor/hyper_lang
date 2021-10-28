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
        src/Hyper/Ast/AstNode.cpp
        src/Hyper/Ast/Expressions/BinaryExpression.cpp
        src/Hyper/Ast/Literals/NumericLiteral.cpp)

set(HEADERS
        include/Hyper/Parser.hpp
        include/Hyper/Scanner.hpp
        include/Hyper/SourceLocation.hpp
        include/Hyper/Token.hpp
        include/Hyper/Ast/AstNode.hpp
        include/Hyper/Ast/Expressions/BinaryExpression.hpp
        include/Hyper/Ast/Expressions/Expression.hpp
        include/Hyper/Ast/Literals/NumericLiteral.hpp
        include/Hyper/Ast/Literals/Literal.hpp)

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
