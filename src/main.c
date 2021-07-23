/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <ast.h>
#include <expressions.h>
#include <generator.h>
#include <lexer.h>
#include <logger.h>
#include <statements.h>
#include <token.h>
#include <symbol_table.h>
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

	for (int i = 0; i < 1024; ++i)
	{
		symbol_table[i].name = "\0";
	}

	generator_init("out.ll");
	generator_generate_pre_code();
	statements_generate();
	generator_generate_post_code();
	generator_free();

	lexer_free();
}
