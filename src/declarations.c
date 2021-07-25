/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "declarations.h"

#include "lexer.h"
#include "generator.h"
#include "statements.h"
#include "symbol_table.h"

#include <stdlib.h>

void generate_variable_declaration(void)
{
	match_token(TOKEN_TYPE_INT);

	char* identifier_name = match_identifier();
	add_global_variable(identifier_name);
	add_symbol(identifier_name);
	free(identifier_name);

	match_semicolon();
}

struct ast* generate_function_declaration(void)
{
	match_token(TOKEN_TYPE_FUNCTION);
	
	char* identifier_name = match_identifier();
	int name_identifier = add_symbol(identifier_name);
	free(identifier_name);
	
	match_left_parenthesis();
	match_right_parenthesis();
	
	match_token(TOKEN_TYPE_RIGHT_ARROW);
	match_token(TOKEN_TYPE_VOID);
	
	struct ast* tree =generate_compound_statement();
	return ast_make_unary(AST_TYPE_FUNCTION, tree, name_identifier);
}
