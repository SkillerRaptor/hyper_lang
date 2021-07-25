/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "statements.h"

#include "ast.h"
#include "declarations.h"
#include "expressions.h"
#include "lexer.h"
#include "logger.h"
#include "symbol_table.h"
#include "types.h"
#include "utils.h"

#include <stdlib.h>

static struct ast* generate_assignment_statement(void)
{
	char* identifier_name = match_identifier();

	int identifier = find_symbol(identifier_name);
	free(identifier_name);

	if (identifier == -1)
	{
		fatal("undeclared variable\n");
		exit_program();

		return NULL;
	}

	struct ast* right = ast_make_leaf(AST_OPERATION_L_VALUE, get_symbol(identifier)->primitive_type, identifier);

	match_token(TOKEN_TYPE_ASSIGN);

	struct ast* left = generate_binary_expression(0);

	int left_type = left->type;
	int right_type = right->type;
	if (!type_compatible(&left_type, &right_type, 1))
	{
		fatal("incompatible types\n");
		exit_program();
		
		return NULL;
	}
	
	if (left_type)
	{
		left = ast_make_unary(left_type, right->type, left, 0);
	}
	
	struct ast* ast = ast_make_node(AST_OPERATION_ASSIGN, PRIMITIVE_TYPE_INT, left, NULL, right, 0);
	return ast;
}

static struct ast* generate_if_statement(void)
{
	match_token(TOKEN_TYPE_IF);
	match_left_parenthesis();

	struct ast* conditional_tree = generate_binary_expression(0);
	if (conditional_tree->operation < AST_OPERATION_EQUAL || conditional_tree->operation > AST_OPERATION_GREATER_EQUAL)
	{
		fatal("bad comparison operator\n");
		exit_program();

		return NULL;
	}

	match_right_parenthesis();

	struct ast* true_tree = generate_compound_statement();

	struct ast* false_tree = NULL;
	if (token.type == TOKEN_TYPE_ELSE)
	{
		next_token();

		false_tree = generate_compound_statement();
	}

	struct ast* ast = ast_make_node(AST_OPERATION_IF, PRIMITIVE_TYPE_NONE, conditional_tree, true_tree, false_tree, 0);
	return ast;
}

static struct ast* generate_print_statement(void)
{
	match_token(TOKEN_TYPE_PRINT);

	struct ast* ast = generate_binary_expression(0);

	int left_type = PRIMITIVE_TYPE_INT;
	int right_type = ast->type;
	if (!type_compatible(&left_type, &right_type, 0))
	{
		fatal("incompatible types\n");
		exit_program();

		return NULL;
	}

	if (right_type)
	{
		ast = ast_make_unary(right_type, PRIMITIVE_TYPE_INT, ast, 0);
	}
	
	ast = ast_make_unary(AST_OPERATION_PRINT, PRIMITIVE_TYPE_NONE, ast, 0);
	return ast;
}

static struct ast* generate_while_statement(void)
{
	match_token(TOKEN_TYPE_WHILE);
	match_left_parenthesis();

	struct ast* conditional_tree = generate_binary_expression(0);
	if (conditional_tree->operation < AST_OPERATION_EQUAL || conditional_tree->operation > AST_OPERATION_GREATER_EQUAL)
	{
		fatal("bad comparison operator\n");
		exit_program();

		return NULL;
	}

	match_right_parenthesis();

	struct ast* body_tree = generate_compound_statement();
	struct ast* ast = ast_make_node(AST_OPERATION_WHILE, PRIMITIVE_TYPE_NONE, conditional_tree, NULL, body_tree, 0);
	return ast;
}

static struct ast* generate_for_statement(void)
{
	match_token(TOKEN_TYPE_FOR);
	match_left_parenthesis();

	struct ast* pre_operation_tree = generate_single_statement();
	match_semicolon();

	struct ast* conditional_tree = generate_binary_expression(0);
	if (conditional_tree->operation < AST_OPERATION_EQUAL || conditional_tree->operation > AST_OPERATION_GREATER_EQUAL)
	{
		fatal("bad comparison operator\n");
		exit_program();

		return NULL;
	}
	match_semicolon();

	struct ast* post_operation_tree = generate_single_statement();
	match_right_parenthesis();

	struct ast* body_tree = generate_compound_statement();

	struct ast* tree = ast_make_node(AST_OPERATION_GLUE, PRIMITIVE_TYPE_NONE, body_tree, NULL, post_operation_tree, 0);
	tree = ast_make_node(AST_OPERATION_WHILE, PRIMITIVE_TYPE_NONE, conditional_tree, NULL, tree, 0);

	struct ast* ast = ast_make_node(AST_OPERATION_GLUE, PRIMITIVE_TYPE_NONE, pre_operation_tree, NULL, tree, 0);
	return ast;
}

struct ast* generate_single_statement(void)
{
	switch (token.type)
	{
	case TOKEN_TYPE_IDENTIFIER:
		return generate_assignment_statement();
	case TOKEN_TYPE_CHAR:
	case TOKEN_TYPE_INT:
		generate_variable_declaration();
		return NULL;
	case TOKEN_TYPE_PRINT:
		return generate_print_statement();
	case TOKEN_TYPE_IF:
		return generate_if_statement();
	case TOKEN_TYPE_WHILE:
		return generate_while_statement();
	case TOKEN_TYPE_FOR:
		return generate_for_statement();
	default:
		break;
	}

	fatal("syntax error\n");
	exit_program();

	return NULL;
}

struct ast* generate_compound_statement(void)
{
	struct ast* left = NULL;

	match_left_brace();

	while (1)
	{
		struct ast* tree = generate_single_statement();

		if (tree != NULL && (tree->operation == AST_OPERATION_PRINT || tree->operation == AST_OPERATION_ASSIGN))
		{
			match_semicolon();
		}

		if (tree != NULL)
		{
			if (left == NULL)
			{
				left = tree;
			}
			else
			{
				left = ast_make_node(AST_OPERATION_GLUE, PRIMITIVE_TYPE_NONE, left, NULL, tree, 0);
			}
		}

		if (token.type == TOKEN_TYPE_RIGHT_BRACE)
		{
			match_right_brace();
			return left;
		}
	}
}
