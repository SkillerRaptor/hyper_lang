/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <ast.h>
#include <expressions.h>
#include <interpreter.h>
#include <lexer.h>
#include <logger.h>
#include <token.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	setbuf(stdout, NULL);

	if (argc < 2)
	{
		fatal("no input files specified\n");
		return 1;
	}

	const char* file_name = argv[1];
	if (!lexer_init(file_name))
	{
		lexer_free();
		return 1;
	}

	lexer_next_token(&token);
	struct ast* ast = ast_binary_expression(0);
	info("%u\n", interpreter_interpret_ast(ast));

	lexer_free();
}
