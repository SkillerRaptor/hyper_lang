/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <expressions.h>
#include <lexer.h>
#include <logger.h>
#include <token.h>
#include <stdlib.h>

int expressions_arithmetic_operation(int token_type)
{
	switch (token_type)
	{
	case TOKEN_TYPE_PLUS:
		return AST_TYPE_ADD;
	case TOKEN_TYPE_MINUS:
		return AST_TYPE_SUBTRACT;
	case TOKEN_TYPE_STAR:
		return AST_TYPE_MULTIPLY;
	case TOKEN_TYPE_SLASH:
		return AST_TYPE_DIVIDE;
	default:
		break;
	}

	fatal("expressions.c: unexpected token type: %u\n", token_type);
	return -1;
}

struct ast* ast_primary(void)
{
	switch (token.type)
	{
	case TOKEN_TYPE_INT_LITERAL:
	{
		struct ast* ast = ast_make_leaf(AST_TYPE_INT_LITERAL, token.value.int_value);
		lexer_next_token(&token);
		return ast;
	}
	default:
		break;
	}

	fatal("expressions.c: syntax error\n");
	return NULL;
}

struct ast* ast_binary_expression(void)
{
	struct ast* left = ast_primary();
	if (token.type == TOKEN_TYPE_EOF)
	{
		return left;
	}

	int node_type = expressions_arithmetic_operation(token.type);
	lexer_next_token(&token);

	struct ast* right = ast_binary_expression();

	struct ast* ast = ast_make_node(node_type, left, right, 0);
	return ast;
}
