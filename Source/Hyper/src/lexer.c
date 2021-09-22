/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "lexer.h"

#include "errors.h"
#include "logger.h"
#include "utils.h"

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int lexer_init(struct lexer** lexer, const char* file_path)
{
	assert(file_path != NULL);
	
	*lexer = malloc(sizeof(struct lexer));
	if (*lexer == NULL)
	{
		return HYPER_OUT_OF_MEMORY;
	}
	
	if (hyper_duplicate_string(file_path, &(*lexer)->file_path) != HYPER_SUCCESS)
	{
		return HYPER_OUT_OF_MEMORY;
	}
	
	if (hyper_read_file(file_path, &(*lexer)->text) != HYPER_SUCCESS)
	{
		hyper_error("%s: No such file or directory\n", file_path);
		return HYPER_IO_ERROR;
	}
	
	(*lexer)->text_size = (int) strlen((*lexer)->text);
	(*lexer)->position = 0;
	(*lexer)->line = 1;
	(*lexer)->column = 1;
	
	return EXIT_SUCCESS;
}

void lexer_free(struct lexer* lexer)
{
	if (lexer == NULL)
	{
		return;
	}
	
	if (lexer->file_path != NULL)
	{
		free(lexer->file_path);
	}
	
	if (lexer->text != NULL)
	{
		free(lexer->text);
	}
	
	free(lexer);
}

static char lexer_next_character(struct lexer* lexer)
{
	if (lexer->position >= lexer->text_size)
	{
		return '\0';
	}
	
	char character = lexer->text[lexer->position++];
	
	++lexer->column;
	
	if (character == '\n')
	{
		++lexer->line;
		lexer->column = 1;
	}
	
	return character;
}

static void lexer_skip_whitespace(struct lexer* lexer)
{
	char character;
	
	do
	{
		character = lexer_next_character(lexer);
	} while (character == ' ' ||
	         character == '\t' ||
	         character == '\n' ||
	         character == '\r' ||
	         character == '\f');
	
	--lexer->position;
}

static char* lexer_scan_decimal_number(struct lexer* lexer, char character)
{
	int value = 0;
	size_t length = 1;
	
	int character_value = character - '0';
	while (character_value >= 0 && character_value <= 9)
	{
		value = value * 10 + character_value;
		++length;
		character_value = lexer_next_character(lexer) - '0';
	}
	
	--lexer->position;
	
	char* string = malloc(length);
	snprintf(string, length, "%i", value);
	
	return string;
}

static char* lexer_scan_numeric_literal(struct lexer* lexer, char character)
{
	// TODO(SkillerRaptor): Check for `0b` and handle binary numbers
	// TODO(SkillerRaptor): Check for `0x` and handle hex numbers
	// TODO(SkillerRaptor): Check for `0o` and handle octal numbers
	return lexer_scan_decimal_number(lexer, character);
}

struct token lexer_next_token(struct lexer* lexer)
{
	lexer_skip_whitespace(lexer);
	
	struct token token;
	token.value = "";
	token.type = TOKEN_TYPE_EOF;
	
	char character = lexer_next_character(lexer);
	switch (character)
	{
	case '+':
		token.value = "+";
		token.type = TOKEN_TYPE_PLUS;
		break;
	case '-':
		token.value = "-";
		token.type = TOKEN_TYPE_MINUS;
		break;
	case '*':
		token.value = "*";
		token.type = TOKEN_TYPE_STAR;
		break;
	case '/':
		token.value = "/";
		token.type = TOKEN_TYPE_SLASH;
		break;
	default:
		if (lexer->position >= lexer->text_size)
		{
			break;
		}
		
		if (isdigit(character))
		{
			token.value = lexer_scan_numeric_literal(lexer, character);
			token.type = TOKEN_TYPE_NUMERIC_LITERAL;
			break;
		}
		
		// TODO(SkillerRaptor): Handle unexpected character
		
		hyper_terminate_compilation();
		
		break;
	}
	
	return token;
}
