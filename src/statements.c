/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <ast.h>
#include <expressions.h>
#include <generator.h>
#include <lexer.h>
#include <statements.h>

void statements_generate(void)
{
	struct ast* ast;
	int reg;

	while (1)
	{
		lexer_match(TOKEN_TYPE_PRINT, "print");

		ast = ast_binary_expression(0);
		reg = generator_generate_ast(ast);
		generator_generate_print_int(reg);

		lexer_match_semicolon();

		if (token.type == TOKEN_TYPE_EOF)
		{
			return;
		}
	}
}
