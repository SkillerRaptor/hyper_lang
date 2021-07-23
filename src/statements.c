/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <ast.h>
#include <declarations.h>
#include <expressions.h>
#include <generator.h>
#include <lexer.h>
#include <logger.h>
#include <statements.h>
#include <symbol_table.h>
#include <utils.h>
#include <stdlib.h>

void statements_generate_print_statement(void)
{
	lexer_match(TOKEN_TYPE_PRINT);

	struct ast* ast = ast_binary_expression(0);
	int reg = generator_generate_ast(ast, -1);
	generator_generate_print_int(reg);

	lexer_match_semicolon();
}

void statements_generate_assignment_statement(void)
{
	char* identifier_name = strdup(token.value.identifier);
	lexer_match_identifier();

	int identifier = symbol_table_find_global(identifier_name);
	if (identifier == -1)
	{
		fatal("statements.c: undeclared variable %s", identifier_name);
		free(identifier_name);
		return;
	}
	
	free(identifier_name);
	
	struct ast* right = ast_make_leaf(AST_TYPE_L_VALUE, identifier);

	lexer_match(TOKEN_TYPE_ASSIGN);

	struct ast* left = ast_binary_expression(0);

	struct ast* ast = ast_make_node(AST_TYPE_ASSIGN, left, right, 0);
	generator_generate_ast(ast, -1);

	lexer_match_semicolon();
}

void statements_generate(void)
{
	while (1)
	{
		switch (token.type)
		{
		case TOKEN_TYPE_PRINT:
			statements_generate_print_statement();
			break;
		case TOKEN_TYPE_INT:
			declarations_generate_variable_declaration();
			break;
		case TOKEN_TYPE_IDENTIFIER:
			statements_generate_assignment_statement();
			break;
		case TOKEN_TYPE_EOF:
			return;
		default:
			fatal("statements.c: syntax error with token %s\n", token_type_to_string(token.type));
			return;
		}
	}
}
