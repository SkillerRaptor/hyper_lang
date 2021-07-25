/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPERLANG_AST_H_
#define HYPERLANG_AST_H_

enum
{
	AST_OPERATION_ADD,
	AST_OPERATION_SUBTRACT,
	AST_OPERATION_MULTIPLY,
	AST_OPERATION_DIVIDE,

	AST_OPERATION_EQUAL,
	AST_OPERATION_NOT_EQUAL,
	AST_OPERATION_LESS_THAN,
	AST_OPERATION_GREATER_THAN,
	AST_OPERATION_LESS_EQUAL,
	AST_OPERATION_GREATER_EQUAL,

	AST_OPERATION_INT_LITERAL,
	AST_OPERATION_IDENTIFIER,
	AST_OPERATION_L_VALUE,
	AST_OPERATION_ASSIGN,

	AST_OPERATION_PRINT,
	AST_OPERATION_IF,
	AST_OPERATION_WHILE,
	AST_OPERATION_GLUE,
	AST_OPERATION_FUNCTION,
	AST_OPERATION_WIDEN
};

struct ast
{
	int operation;
	int type;

	struct ast* left;
	struct ast* middle;
	struct ast* right;

	union
	{
		int int_value;
		int identifier;
	} value;
};

struct ast* ast_make_node(int operation, int type, struct ast* left, struct ast* middle, struct ast* right, int int_value);
struct ast* ast_make_leaf(int operation, int type, int int_value);
struct ast* ast_make_unary(int operation, int type, struct ast* left, int int_value);

const char* ast_type_to_string(int operation);

#endif // HYPERLANG_AST_H_
