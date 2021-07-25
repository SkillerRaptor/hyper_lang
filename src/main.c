/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "declarations.h"
#include "generator.h"
#include "lexer.h"
#include "logger.h"
#include "statements.h"
#include "symbol_table.h"
#include "utils.h"

#include <stdio.h>

int main(int argc, char** argv)
{
	setbuf(stdout, NULL);

	if (argc < 2)
	{
		fatal("no input file specified\n");
		exit_program();
		
		return 1;
	}

	const char* file_name = argv[1];
	init_lexer(file_name);
	init_symbols();
	init_generator("out.ll");
	
	generate_pre_code();
	while (1)
	{
		struct ast* tree = generate_function_declaration();
		generate_ast(tree, NULL, NULL, 0);
		if (token.type == TOKEN_TYPE_EOF)
		{
			break;
		}
	}
	
	generate_code();
	
	free_generator();
	free_lexer();
	
	return 0;
}
