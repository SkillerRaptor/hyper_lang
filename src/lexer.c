/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <lexer.h>
#include <logger.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

static int line;
static char putback;
static FILE* file;

int lexer_init(const char* file_name)
{
	line = 0;
	putback = '\0';
	file = fopen(file_name, "r");

	if (file == NULL)
	{
		fatal("lexer.c: failed to open file %s\n", file_name);
		return 1;
	}

	return 0;
}

void lexer_free()
{
	if (file == NULL)
	{
		return;
	}

	fclose(file);
}

static char lexer_next_character(void)
{
	char character;

	if (putback != '\0')
	{
		character = putback;
		putback = '\0';
		return character;
	}

	character = (char) fgetc(file);
	if (character == '\n')
	{
		++line;
	}

	return character;
}

static void lexer_skip_whitespace(void)
{
	char character = lexer_next_character();

	while (character == ' ' || character == '\t' || character == '\n' || character == '\r' || character == '\f')
	{
		character = lexer_next_character();
	}

	putback = character;
}

static int chrpos(char* string, char character)
{
	char* pointer = strchr(string, character);
	return (pointer ? pointer - string : -1);
}

static int lexer_scan_int(char character)
{
	int i = 0;
	int value = 0;

	while ((i = chrpos("0123456789", character)) >= 0)
	{
		value = value * 10 + i;
		character = lexer_next_character();
	}

	putback = character;
	return value;
}

int lexer_next_token(struct token* token)
{
	lexer_skip_whitespace();

	char character = lexer_next_character();
	switch (character)
	{
	case '+':
		token->type = TOKEN_TYPE_PLUS;
		break;
	case '-':
		token->type = TOKEN_TYPE_MINUS;
		break;
	case '*':
		token->type = TOKEN_TYPE_STAR;
		break;
	case '/':
		token->type = TOKEN_TYPE_SLASH;
		break;
	case EOF:
		return 1;
	default:
		if (isdigit(character))
		{
			token->type = TOKEN_TYPE_INT_LITERAL;
			token->value.int_value = lexer_scan_int(character);
			break;
		}

		token->type = TOKEN_TYPE_EOF;
		warning("lexer.c: unexpected character %c\n", character);

		break;
	}

	return 0;
}
