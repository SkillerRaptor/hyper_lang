/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "ast.h"

#include "logger.h"
#include "utils.h"

#include <stdlib.h>

struct ast* ast_make_node(int type, struct ast* left, struct ast* middle, struct ast* right, int int_value)
{
	struct ast* ast = malloc(sizeof(struct ast));
	if (ast == NULL)
	{
		fatal("out of memory\n");
		exit_program();

		return NULL;
	}

	ast->type = type;
	ast->left = left;
	ast->middle = middle;
	ast->right = right;
	ast->value.int_value = int_value;

	return ast;
}

struct ast* ast_make_leaf(int type, int int_value)
{
	return ast_make_node(type, NULL, NULL, NULL, int_value);
}

struct ast* ast_make_unary(int type, struct ast* left, int int_value)
{
	return ast_make_node(type, left, NULL, NULL, int_value);
}

const char* ast_type_to_string(int type)
{
	switch (type)
	{
	case AST_TYPE_ADD:
		return "AST_TYPE_ADD";
	case AST_TYPE_SUBTRACT:
		return "AST_TYPE_SUBTRACT";
	case AST_TYPE_MULTIPLY:
		return "AST_TYPE_MULTIPLY";
	case AST_TYPE_DIVIDE:
		return "AST_TYPE_DIVIDE";
	case AST_TYPE_EQUAL:
		return "AST_TYPE_EQUAL";
	case AST_TYPE_NOT_EQUAL:
		return "AST_TYPE_NOT_EQUAL";
	case AST_TYPE_LESS_THAN:
		return "AST_TYPE_LESS_THAN";
	case AST_TYPE_GREATER_THAN:
		return "AST_TYPE_GREATER_THAN";
	case AST_TYPE_LESS_EQUAL:
		return "AST_TYPE_LESS_EQUAL";
	case AST_TYPE_GREATER_EQUAL:
		return "AST_TYPE_GREATER_EQUAL";
	case AST_TYPE_INT_LITERAL:
		return "AST_TYPE_INT_LITERAL";
	case AST_TYPE_IDENTIFIER:
		return "AST_TYPE_IDENTIFIER";
	case AST_TYPE_L_VALUE:
		return "AST_TYPE_L_VALUE";
	case AST_TYPE_ASSIGN:
		return "AST_TYPE_ASSIGN";
	case AST_TYPE_PRINT:
		return "AST_TYPE_PRINT";
	case AST_TYPE_IF:
		return "AST_TYPE_IF";
	case AST_TYPE_WHILE:
		return "AST_TYPE_WHILE";
	case AST_TYPE_GLUE:
		return "AST_TYPE_GLUE";
	default:
		break;
	}

	return "undefined ast type";
}
