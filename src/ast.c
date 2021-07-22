/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <ast.h>
#include <logger.h>
#include <stdlib.h>

struct ast* ast_make_node(int type, struct ast* left, struct ast* right, int int_value)
{
	struct ast* ast = malloc(sizeof(struct ast));
	if (ast == NULL)
	{
		fatal("ast.c: out of memory\n");
		return NULL;
	}

	ast->type = type;
	ast->left = left;
	ast->right = right;
	ast->int_value = int_value;

	return ast;
}

struct ast* ast_make_leaf(int type, int int_value)
{
	return ast_make_node(type, NULL, NULL, int_value);
}

struct ast* ast_make_unary(int type, struct ast* left, int int_value)
{
	return ast_make_node(type, left, NULL, int_value);
}
