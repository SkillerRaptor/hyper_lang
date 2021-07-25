/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPERLANG_AST_H_
#define HYPERLANG_AST_H_

enum
{
	AST_TYPE_ADD,
	AST_TYPE_SUBTRACT,
	AST_TYPE_MULTIPLY,
	AST_TYPE_DIVIDE,

	AST_TYPE_EQUAL,
	AST_TYPE_NOT_EQUAL,
	AST_TYPE_LESS_THAN,
	AST_TYPE_GREATER_THAN,
	AST_TYPE_LESS_EQUAL,
	AST_TYPE_GREATER_EQUAL,

	AST_TYPE_INT_LITERAL,
	AST_TYPE_IDENTIFIER,
	AST_TYPE_L_VALUE,
	AST_TYPE_ASSIGN,

	AST_TYPE_PRINT,
	AST_TYPE_IF,
	AST_TYPE_WHILE,
	AST_TYPE_GLUE,
	AST_TYPE_FUNCTION
};

struct ast
{
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

struct ast* ast_make_node(int type, struct ast* left, struct ast* middle, struct ast* right, int int_value);
struct ast* ast_make_leaf(int type, int int_value);
struct ast* ast_make_unary(int type, struct ast* left, int int_value);

const char* ast_type_to_string(int type);

#endif // HYPERLANG_AST_H_
