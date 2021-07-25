/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "ast.h"

#include "logger.h"
#include "utils.h"

#include <stdlib.h>

struct ast* ast_make_node(int operation, int type, struct ast* left, struct ast* middle, struct ast* right, int int_value)
{
	struct ast* ast = malloc(sizeof(struct ast));
	if (ast == NULL)
	{
		fatal("out of memory\n");
		exit_program();

		return NULL;
	}

	ast->operation = operation;
	ast->type = type;
	ast->left = left;
	ast->middle = middle;
	ast->right = right;
	ast->value.int_value = int_value;

	return ast;
}

struct ast* ast_make_leaf(int operation, int type, int int_value)
{
	return ast_make_node(operation, type, NULL, NULL, NULL, int_value);
}

struct ast* ast_make_unary(int operation, int type, struct ast* left, int int_value)
{
	return ast_make_node(operation, type, left, NULL, NULL, int_value);
}

const char* ast_type_to_string(int operation)
{
	switch (operation)
	{
	case AST_OPERATION_ADD:
		return "AST_OPERATION_ADD";
	case AST_OPERATION_SUBTRACT:
		return "AST_OPERATION_SUBTRACT";
	case AST_OPERATION_MULTIPLY:
		return "AST_OPERATION_MULTIPLY";
	case AST_OPERATION_DIVIDE:
		return "AST_OPERATION_DIVIDE";
	case AST_OPERATION_EQUAL:
		return "AST_OPERATION_EQUAL";
	case AST_OPERATION_NOT_EQUAL:
		return "AST_OPERATION_NOT_EQUAL";
	case AST_OPERATION_LESS_THAN:
		return "AST_OPERATION_LESS_THAN";
	case AST_OPERATION_GREATER_THAN:
		return "AST_OPERATION_GREATER_THAN";
	case AST_OPERATION_LESS_EQUAL:
		return "AST_OPERATION_LESS_EQUAL";
	case AST_OPERATION_GREATER_EQUAL:
		return "AST_OPERATION_GREATER_EQUAL";
	case AST_OPERATION_INT_LITERAL:
		return "AST_OPERATION_INT_LITERAL";
	case AST_OPERATION_IDENTIFIER:
		return "AST_OPERATION_IDENTIFIER";
	case AST_OPERATION_L_VALUE:
		return "AST_OPERATION_L_VALUE";
	case AST_OPERATION_ASSIGN:
		return "AST_OPERATION_ASSIGN";
	case AST_OPERATION_PRINT:
		return "AST_OPERATION_PRINT";
	case AST_OPERATION_IF:
		return "AST_OPERATION_IF";
	case AST_OPERATION_WHILE:
		return "AST_OPERATION_WHILE";
	case AST_OPERATION_GLUE:
		return "AST_OPERATION_GLUE";
	case AST_OPERATION_FUNCTION:
		return "AST_OPERATION_FUNCTION";
	case AST_OPERATION_WIDEN:
		return "AST_OPERATION_WIDEN";
	default:
		break;
	}

	return "undefined ast type";
}
