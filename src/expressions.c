/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "expressions.h"

#include "lexer.h"
#include "logger.h"
#include "token.h"
#include "types.h"
#include "symbol_table.h"
#include "utils.h"

#include <stdlib.h>

static int get_arithmetic_operation(int token_type)
{
	switch (token_type)
	{
	case TOKEN_TYPE_PLUS:
		return AST_OPERATION_ADD;
	case TOKEN_TYPE_MINUS:
		return AST_OPERATION_SUBTRACT;
	case TOKEN_TYPE_STAR:
		return AST_OPERATION_MULTIPLY;
	case TOKEN_TYPE_SLASH:
		return AST_OPERATION_DIVIDE;
	case TOKEN_TYPE_EQUAL:
		return AST_OPERATION_EQUAL;
	case TOKEN_TYPE_NOT_EQUAL:
		return AST_OPERATION_NOT_EQUAL;
	case TOKEN_TYPE_LESS_THAN:
		return AST_OPERATION_LESS_THAN;
	case TOKEN_TYPE_GREATER_THAN:
		return AST_OPERATION_GREATER_THAN;
	case TOKEN_TYPE_LESS_EQUAL:
		return AST_OPERATION_LESS_EQUAL;
	case TOKEN_TYPE_GREATER_EQUAL:
		return AST_OPERATION_GREATER_EQUAL;
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
		int primitive_type = (token.value.int_value >= 0 && token.value.int_value <= 255) ? PRIMITIVE_TYPE_CHAR : PRIMITIVE_TYPE_INT;
		struct ast* ast = ast_make_leaf(AST_OPERATION_INT_LITERAL, primitive_type, token.value.int_value);
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

		struct ast* ast = ast_make_leaf(AST_OPERATION_IDENTIFIER, get_symbol(identifier)->primitive_type, identifier);
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
	if (token_type == TOKEN_TYPE_SEMICOLON || token_type == TOKEN_TYPE_RIGHT_PARENTHESIS)
	{
		return left;
	}

	while (get_token_precedence(token_type) > precedence)
	{
		next_token();

		struct ast* right = generate_binary_expression(get_token_precedence(token_type));
		
		int left_type = left->type;
		int right_type = right->type;
		if (!type_compatible(&left_type, &right_type, 0))
		{
			fatal("incompatible types\n");
			exit_program();
			
			return NULL;
		}
		
		if (left_type)
		{
			left = ast_make_unary(left_type, right->type, left, 0);
		}
		
		if (right_type)
		{
			right = ast_make_unary(right_type, left->type, right, 0);
		}
		
		left = ast_make_node(get_arithmetic_operation(token_type), left->type, left, NULL, right, 0);

		token_type = token.type;
		if (token_type == TOKEN_TYPE_SEMICOLON || token_type == TOKEN_TYPE_RIGHT_PARENTHESIS)
		{
			return left;
		}
	}

	return left;
}
