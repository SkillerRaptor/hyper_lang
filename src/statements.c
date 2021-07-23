/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "statements.h"

#include "ast.h"
#include "declarations.h"
#include "expressions.h"
#include "generator.h"
#include "lexer.h"
#include "logger.h"
#include "symbol_table.h"
#include "utils.h"

#include <stdlib.h>

void generate_assignment_statement(void)
{
	char* identifier_name = match_identifier();

	int identifier = find_symbol(identifier_name);
	free(identifier_name);
	
	if (identifier == -1)
	{
		fatal("undeclared variable\n");
		exit_program();
		
		return;
	}
	
	struct ast* right = ast_make_leaf(AST_TYPE_L_VALUE, identifier);

	match_token(TOKEN_TYPE_ASSIGN);

	struct ast* left = generate_binary_expression(0);
	struct ast* ast = ast_make_node(AST_TYPE_ASSIGN, left, right, 0);
	generate_ast(ast, -1);

	match_semicolon();
}

void generate_print_statement(void)
{
	match_token(TOKEN_TYPE_PRINT);
	
	struct ast* ast = generate_binary_expression(0);
	int reg = generate_ast(ast, -1);
	generate_print_register(reg);
	
	match_semicolon();
}

void generate_statements(void)
{
	int running = 1;
	while (running)
	{
		switch (token.type)
		{
		case TOKEN_TYPE_IDENTIFIER:
			generate_assignment_statement();
			break;
		case TOKEN_TYPE_INT:
			generate_variable_declaration();
			break;
		case TOKEN_TYPE_PRINT:
			generate_print_statement();
			break;
		case TOKEN_TYPE_EOF:
			return;
		default:
			running = 0;
			break;
		}
	}
	
	fatal("syntax error\n");
	exit_program();
}
