/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <declarations.h>
#include <lexer.h>
#include <logger.h>
#include <symbol_table.h>
#include <utils.h>
#include <stdlib.h>

void declarations_generate_variable_declaration(void)
{
	lexer_match(TOKEN_TYPE_INT);
	char* identifier = strdup(token.value.identifier);
	lexer_match_identifier();
	symbol_table_add_global(identifier);
	free(identifier);
	lexer_match_semicolon();
}
