/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "config.h"
#include "errors.h"
#include "lexer.h"
#include "logger.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		hyper_fatal_error("no input files\n");
		hyper_terminate_compilation();
	}
	
	if (strcmp(argv[1], "-v") == 0)
	{
		print("Hyper version v%s\n", HYPER_VERSION);
		return 0;
	}
	
	int file_found = 0;
	for (int i = 1; i < argc; ++i)
	{
		struct lexer* lexer;
		if (lexer_init(&lexer, argv[i]) != HYPER_SUCCESS)
		{
			continue;
		}
		
		file_found = 1;
		
		// TODO(SkillerRaptor): Parsing
		
		struct token token = lexer_next_token(lexer);
		while (token.type != TOKEN_TYPE_EOF)
		{
			hyper_info("token: %s - %s\n", token.value, token_type_to_string(token.type));
			token = lexer_next_token(lexer);
		}
		
		lexer_free(lexer);
	}
	
	if (!file_found)
	{
		hyper_fatal_error("no input files\n");
		hyper_terminate_compilation();
	}
	
	return EXIT_SUCCESS;
}
