/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <interpreter.h>
#include <logger.h>

int interpreter_interpret_ast(struct ast* ast)
{
	int left_value = 0;
	if (ast->left)
	{
		left_value = interpreter_interpret_ast(ast->left);
	}

	int right_value = 0;
	if (ast->right)
	{
		right_value = interpreter_interpret_ast(ast->right);
	}

	switch (ast->type)
	{
	case AST_TYPE_ADD:
		return (left_value + right_value);
	case AST_TYPE_SUBTRACT:
		return (left_value - right_value);
	case AST_TYPE_MULTIPLY:
		return (left_value * right_value);
	case AST_TYPE_DIVIDE:
		return (left_value / right_value);
	case AST_TYPE_INT_LITERAL:
		return (ast->int_value);
	default:
		break;
	}

	fatal("interpreter.c: unknown ast operation %u\n", ast->type);
	return -1;
}
