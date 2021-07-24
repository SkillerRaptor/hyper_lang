/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "expressions.h"

#include "lexer.h"
#include "logger.h"
#include "token.h"
#include "symbol_table.h"
#include "utils.h"

#include <stdlib.h>

static int get_arithmetic_operation(int token_type)
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
	case TOKEN_TYPE_EQUAL:
		return AST_TYPE_EQUAL;
	case TOKEN_TYPE_NOT_EQUAL:
		return AST_TYPE_NOT_EQUAL;
	case TOKEN_TYPE_LESS_THAN:
		return AST_TYPE_LESS_THAN;
	case TOKEN_TYPE_GREATER_THAN:
		return AST_TYPE_GREATER_THAN;
	case TOKEN_TYPE_LESS_EQUAL:
		return AST_TYPE_LESS_EQUAL;
	case TOKEN_TYPE_GREATER_EQUAL:
		return AST_TYPE_GREATER_EQUAL;
	default:
		break;
	}

	fatal("unexpected token type\n");
	exit_program();

	return -1;
}

static int get_token_precedence(int token_type)
{
	int precedence = 0;
	switch (token_type)
	{
	case TOKEN_TYPE_PLUS:
	case TOKEN_TYPE_MINUS:
		precedence = 10;
		break;
	case TOKEN_TYPE_STAR:
	case TOKEN_TYPE_SLASH:
		precedence = 20;
		break;
	case TOKEN_TYPE_EQUAL:
	case TOKEN_TYPE_NOT_EQUAL:
		precedence = 30;
		break;
	case TOKEN_TYPE_LESS_THAN:
	case TOKEN_TYPE_GREATER_THAN:
	case TOKEN_TYPE_LESS_EQUAL:
	case TOKEN_TYPE_GREATER_EQUAL:
		precedence = 40;
		break;
	default:
		break;
	}

	return precedence;
}

static struct ast* ast_primary(void)
{
	switch (token.type)
	{
	case TOKEN_TYPE_INT_LITERAL:
	{
		struct ast* ast = ast_make_leaf(AST_TYPE_INT_LITERAL, token.value.int_value);
		next_token();
		return ast;
	}
	case TOKEN_TYPE_IDENTIFIER:
	{
		int identifier = find_symbol(token.value.identifier);
		if (identifier == -1)
		{
			fatal("unknown variable\n");
			exit_program();

			return NULL;
		}

		struct ast* ast = ast_make_leaf(AST_TYPE_IDENTIFIER, identifier);
		next_token();
		return ast;
	}
	default:
		break;
	}

	fatal("syntax error\n");
	exit_program();

	return NULL;
}

struct ast* generate_binary_expression(int precedence)
{
	struct ast* left = ast_primary();

	int token_type = token.type;
	if (token_type == TOKEN_TYPE_SEMICOLON)
	{
		return left;
	}

	while (get_token_precedence(token_type) > precedence)
	{
		next_token();

		struct ast* right = generate_binary_expression(get_token_precedence(token_type));
		left = ast_make_node(get_arithmetic_operation(token_type), left, NULL, right, 0);

		token_type = token.type;
		if (token_type == TOKEN_TYPE_SEMICOLON)
		{
			return left;
		}
	}

	return left;
}
