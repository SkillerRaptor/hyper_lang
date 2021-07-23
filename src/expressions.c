/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <expressions.h>
#include <lexer.h>
#include <logger.h>
#include <token.h>
#include <symbol_table.h>
#include <stdlib.h>

static int expressions_arithmetic_operation(int token_type)
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

static int expressions_operator_precedence(int token_type)
{
	int precedence = 0;
	switch (token_type)
	{
	case TOKEN_TYPE_EOF:
		precedence = 0;
		break;
	case TOKEN_TYPE_PLUS:
		precedence = 10;
		break;
	case TOKEN_TYPE_MINUS:
		precedence = 10;
		break;
	case TOKEN_TYPE_STAR:
		precedence = 20;
		break;
	case TOKEN_TYPE_SLASH:
		precedence = 20;
		break;
	case TOKEN_TYPE_INT_LITERAL:
		precedence = 0;
		break;
	default:
		break;
	}

	return precedence;
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
	case TOKEN_TYPE_IDENTIFIER:
	{
		int identifier = symbol_table_find_global(token.value.identifier);
		if (identifier == -1)
		{
			fatal("expressions.c: unknown variable %s", token.value.identifier);
			return NULL;
		}

		struct ast* ast = ast_make_leaf(AST_TYPE_IDENTIFIER, identifier);
		lexer_next_token(&token);
		return ast;
	}
	default:
		break;
	}

	fatal("expressions.c: syntax error\n");
	return NULL;
}

struct ast* ast_binary_expression(int precedence)
{
	struct ast* left = ast_primary();

	int token_type = token.type;
	if (token_type == TOKEN_TYPE_SEMICOLON)
	{
		return left;
	}

	while (expressions_operator_precedence(token_type) > precedence)
	{
		lexer_next_token(&token);

		struct ast* right = ast_binary_expression(expressions_operator_precedence(token_type));

		left = ast_make_node(expressions_arithmetic_operation(token_type), left, right, 0);

		token_type = token.type;
		if (token_type == TOKEN_TYPE_SEMICOLON)
		{
			return left;
		}
	}

	return left;
}
