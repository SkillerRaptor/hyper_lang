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
#include "types.h"

#include <stdlib.h>

void generate_variable_declaration(void)
{
	int token_type = token.type;
	next_token();

	char* identifier_name = match_identifier();
	int identifier = add_symbol(identifier_name, token_to_primitive_type(token_type), STRUCTURAL_TYPE_VARIABLE);
	add_global_variable(identifier);
	free(identifier_name);

	match_semicolon();
}

struct ast* generate_function_declaration(void)
{
	match_token(TOKEN_TYPE_FUNCTION);

	char* identifier_name = match_identifier();
	int name_identifier = add_symbol(identifier_name, PRIMITIVE_TYPE_VOID, STRUCTURAL_TYPE_FUNCTION);
	free(identifier_name);

	match_left_parenthesis();
	match_right_parenthesis();

	match_token(TOKEN_TYPE_RIGHT_ARROW);
	match_token(TOKEN_TYPE_VOID);

	struct ast* tree = generate_compound_statement();
	return ast_make_unary(AST_OPERATION_FUNCTION, PRIMITIVE_TYPE_VOID, tree, name_identifier);
}
