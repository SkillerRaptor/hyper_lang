/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

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
	if (lexer_init(file_name))
	{
		lexer_free();
		return 1;
	}

	struct token token;
	while (!lexer_next_token(&token))
	{
		info("Token %u\n", token.type);
	}

	lexer_free();
}
