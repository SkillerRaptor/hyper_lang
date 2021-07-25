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

	struct ast* right = ast_make_leaf(AST_TYPE_L_VALUE, identifier);

	match_token(TOKEN_TYPE_ASSIGN);

	struct ast* left = generate_binary_expression(0);
	struct ast* ast = ast_make_node(AST_TYPE_ASSIGN, left, NULL, right, 0);

	match_semicolon();

	return ast;
}

static struct ast* generate_if_statement(void)
{
	match_token(TOKEN_TYPE_IF);
	match_left_parenthesis();

	struct ast* conditional_tree = generate_binary_expression(0);
	if (conditional_tree->type < AST_TYPE_EQUAL || conditional_tree->type > AST_TYPE_GREATER_EQUAL)
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

	return ast_make_node(AST_TYPE_IF, conditional_tree, true_tree, false_tree, 0);
}

static struct ast* generate_print_statement(void)
{
	match_token(TOKEN_TYPE_PRINT);

	struct ast* ast = generate_binary_expression(0);
	ast = ast_make_unary(AST_TYPE_PRINT, ast, 0);

	match_semicolon();

	return ast;
}

static struct ast* generate_while_statement(void)
{
	match_token(TOKEN_TYPE_WHILE);
	match_left_parenthesis();
	
	struct ast* conditional_tree = generate_binary_expression(0);
	if (conditional_tree->type < AST_TYPE_EQUAL || conditional_tree->type > AST_TYPE_GREATER_EQUAL)
	{
		fatal("bad comparison operator\n");
		exit_program();
		
		return NULL;
	}
	
	match_right_parenthesis();
	
	struct ast* body_tree = generate_compound_statement();
	return ast_make_node(AST_TYPE_WHILE, conditional_tree, NULL, body_tree, 0);
}

struct ast* generate_compound_statement(void)
{
	struct ast* left = NULL;

	match_left_brace();

	while (1)
	{
		struct ast* tree = NULL;

		switch (token.type)
		{
		case TOKEN_TYPE_IDENTIFIER:
			tree = generate_assignment_statement();
			break;
		case TOKEN_TYPE_INT:
			generate_variable_declaration();
			break;
		case TOKEN_TYPE_PRINT:
			tree = generate_print_statement();
			break;
		case TOKEN_TYPE_IF:
			tree = generate_if_statement();
			break;
		case TOKEN_TYPE_WHILE:
			tree = generate_while_statement();
			break;
		case TOKEN_TYPE_RIGHT_BRACE:
			match_right_brace();
			return left;
		default:
			fatal("syntax error\n");
			exit_program();

			break;
		}

		if (tree == NULL)
		{
			continue;
		}

		if (left == NULL)
		{
			left = tree;
			continue;
		}

		left = ast_make_node(AST_TYPE_GLUE, left, NULL, tree, 0);
	}
}
