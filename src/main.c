/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

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
	struct ast* tree = generate_compound_statement();
	generate_ast(tree, NULL, NULL, 0);
	generate_post_code();
	
	generate_code();
	
	free_generator();
	free_lexer();
	
	return 0;
}
