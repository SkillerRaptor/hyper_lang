/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "declarations.h"

#include "lexer.h"
#include "generator.h"
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
