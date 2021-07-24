/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "lexer.h"

#include "logger.h"
#include "utils.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

static char putback = '\0';
static FILE* file = NULL;

struct token token;

void init_lexer(const char* file_name)
{
	file = fopen(file_name, "r");
	if (file == NULL)
	{
		fatal("failed to open file\n");
		exit_program();

		return;
	}

	next_token();
}

void free_lexer()
{
	fclose(file);
}

static char get_next_character(void)
{
	if (putback != '\0')
	{
		char character = putback;
		putback = '\0';
		return character;
	}

	return (char) fgetc(file);
}

static void skip_whitespace(void)
{
	char character = get_next_character();
	while (character == ' ' || character == '\t' || character == '\n' || character == '\r' || character == '\f')
	{
		character = get_next_character();
	}

	putback = character;
}

static void scan_int(char character, int* integer)
{
	int position = character_position("0123456789", character);
	while (position >= 0)
	{
		*integer = *integer * 10 + position;
		character = get_next_character();

		position = character_position("0123456789", character);
	}

	putback = character;
}

static void scan_string(char* buffer)
{
	char character = get_next_character();
	for (int position = 0; position < BUFFER_SIZE_LIMIT; ++position)
	{
		if (character == '"')
		{
			buffer[position] = '\0';
			return;
		}

		buffer[position] = character;
		character = get_next_character();
	}

	fatal("string literal is too long\n");
	exit_program();
}

static void scan_identifier(char character, char* buffer)
{
	int position = 0;
	while (isalpha(character) || isdigit(character) || character == '_')
	{
		if (position == BUFFER_SIZE_LIMIT)
		{
			fatal("identifier name is too long\n");
			exit_program();

			return;
		}

		buffer[position++] = character;
		character = get_next_character();
	}

	putback = character;
	buffer[position] = '\0';
}

#define DEFINE_KEYWORD(identifier, token_type) \
	do                                         \
	{                                          \
		if (!strcmp(keyword, identifier))      \
		{                                      \
			return token_type;                 \
		}                                      \
	} while (0)

static int get_keyword(const char* keyword)
{
	switch (*keyword)
	{
	case 'b':
		DEFINE_KEYWORD("bool", TOKEN_TYPE_BOOL);
		DEFINE_KEYWORD("break", TOKEN_TYPE_BREAK);
		DEFINE_KEYWORD("breakall", TOKEN_TYPE_BREAKALL);
		break;
	case 'c':
		DEFINE_KEYWORD("continue", TOKEN_TYPE_CONTINUE);
		break;
	case 'd':
		DEFINE_KEYWORD("do", TOKEN_TYPE_DO);
		DEFINE_KEYWORD("double", TOKEN_TYPE_DOUBLE);
		break;
	case 'e':
		DEFINE_KEYWORD("else", TOKEN_TYPE_ELSE);
		DEFINE_KEYWORD("enum", TOKEN_TYPE_ENUM);
		DEFINE_KEYWORD("export", TOKEN_TYPE_EXPORT);
		break;
	case 'f':
		DEFINE_KEYWORD("float", TOKEN_TYPE_FLOAT);
		DEFINE_KEYWORD("for", TOKEN_TYPE_FOR);
		DEFINE_KEYWORD("function", TOKEN_TYPE_FUNCTION);
		break;
	case 'i':
		DEFINE_KEYWORD("if", TOKEN_TYPE_IF);
		DEFINE_KEYWORD("import", TOKEN_TYPE_IMPORT);
		DEFINE_KEYWORD("int", TOKEN_TYPE_INT);
		DEFINE_KEYWORD("int8", TOKEN_TYPE_INT8);
		DEFINE_KEYWORD("int16", TOKEN_TYPE_INT16);
		DEFINE_KEYWORD("int32", TOKEN_TYPE_INT32);
		DEFINE_KEYWORD("int64", TOKEN_TYPE_INT64);
		break;
	case 'm':
		DEFINE_KEYWORD("mutable", TOKEN_TYPE_MUTABLE);
		break;
	case 'o':
		DEFINE_KEYWORD("of", TOKEN_TYPE_OF);
		DEFINE_KEYWORD("override", TOKEN_TYPE_OVERRIDE);
		break;
	case 'p':
		DEFINE_KEYWORD("package", TOKEN_TYPE_PACKAGE);
		DEFINE_KEYWORD("print", TOKEN_TYPE_PRINT);
		break;
	case 'r':
		DEFINE_KEYWORD("return", TOKEN_TYPE_RETURN);
		break;
	case 's':
		DEFINE_KEYWORD("string", TOKEN_TYPE_STRING);
		DEFINE_KEYWORD("struct", TOKEN_TYPE_STRUCT);
		break;
	case 'u':
		DEFINE_KEYWORD("uint", TOKEN_TYPE_UINT);
		DEFINE_KEYWORD("uint8", TOKEN_TYPE_UINT8);
		DEFINE_KEYWORD("uint16", TOKEN_TYPE_UINT16);
		DEFINE_KEYWORD("uint32", TOKEN_TYPE_UINT32);
		DEFINE_KEYWORD("uint64", TOKEN_TYPE_UINT64);
		DEFINE_KEYWORD("union", TOKEN_TYPE_UNION);
		break;
	case 'v':
		DEFINE_KEYWORD("virtual", TOKEN_TYPE_VIRTUAL);
		DEFINE_KEYWORD("void", TOKEN_TYPE_VOID);
		break;
	case 'w':
		DEFINE_KEYWORD("while", TOKEN_TYPE_WHILE);
		break;
	default:
		break;
	}

	return -1;
}

#define DEFINE_SIMPLE_TOKEN(token_value, token_type) \
	case token_value:                                \
		token.type = token_type;                     \
		break

#define DEFINE_MULTIPLE_TOKENS(token_value) \
	case token_value:                       \
		character = get_next_character()

#define DEFINE_MULTIPLE_TOKEN_CASE(token_case, token_type) \
	if (character == (token_case))                         \
	{                                                      \
		token.type = token_type;                           \
		break;                                             \
	}

#define DEFINE_MULTIPLE_TOKENS_END(token_type) \
	putback = character;                       \
	token.type = token_type;                   \
	break

void next_token()
{
	skip_whitespace();

	memset(&token.value, 0, sizeof(token.value));

	char character = get_next_character();
	switch (character)
	{
		DEFINE_SIMPLE_TOKEN(EOF, TOKEN_TYPE_EOF);
		DEFINE_SIMPLE_TOKEN(',', TOKEN_TYPE_COMMA);
		DEFINE_SIMPLE_TOKEN('.', TOKEN_TYPE_DOT);
		DEFINE_SIMPLE_TOKEN(':', TOKEN_TYPE_COLON);
		DEFINE_SIMPLE_TOKEN(';', TOKEN_TYPE_SEMICOLON);
		DEFINE_SIMPLE_TOKEN('{', TOKEN_TYPE_LEFT_BRACE);
		DEFINE_SIMPLE_TOKEN('}', TOKEN_TYPE_RIGHT_BRACE);
		DEFINE_SIMPLE_TOKEN('(', TOKEN_TYPE_LEFT_PARENTHESIS);
		DEFINE_SIMPLE_TOKEN(')', TOKEN_TYPE_RIGHT_PARENTHESIS);
		DEFINE_SIMPLE_TOKEN('[', TOKEN_TYPE_LEFT_BRACKET);
		DEFINE_SIMPLE_TOKEN(']', TOKEN_TYPE_RIGHT_BRACKET);

		DEFINE_MULTIPLE_TOKENS('+');
		DEFINE_MULTIPLE_TOKEN_CASE('+', TOKEN_TYPE_INCREMENT)
		DEFINE_MULTIPLE_TOKEN_CASE('=', TOKEN_TYPE_PLUS_EQUAL)
		DEFINE_MULTIPLE_TOKENS_END(TOKEN_TYPE_PLUS);

		DEFINE_MULTIPLE_TOKENS('-');
		DEFINE_MULTIPLE_TOKEN_CASE('-', TOKEN_TYPE_DECREMENT)
		DEFINE_MULTIPLE_TOKEN_CASE('=', TOKEN_TYPE_MINUS_EQUAL)
		DEFINE_MULTIPLE_TOKEN_CASE('>', TOKEN_TYPE_RIGHT_ARROW)
		DEFINE_MULTIPLE_TOKENS_END(TOKEN_TYPE_MINUS);

		DEFINE_MULTIPLE_TOKENS('*');
		DEFINE_MULTIPLE_TOKEN_CASE('=', TOKEN_TYPE_STAR_EQUAL)
		DEFINE_MULTIPLE_TOKENS_END(TOKEN_TYPE_STAR);

		DEFINE_MULTIPLE_TOKENS('/');
		DEFINE_MULTIPLE_TOKEN_CASE('=', TOKEN_TYPE_SLASH_EQUAL)
		DEFINE_MULTIPLE_TOKENS_END(TOKEN_TYPE_SLASH);

		DEFINE_MULTIPLE_TOKENS('%');
		DEFINE_MULTIPLE_TOKEN_CASE('=', TOKEN_TYPE_MODULAR_EQUAL)
		DEFINE_MULTIPLE_TOKENS_END(TOKEN_TYPE_MODULAR);

		DEFINE_MULTIPLE_TOKENS('&');
		DEFINE_MULTIPLE_TOKEN_CASE('=', TOKEN_TYPE_BITWISE_AND_EQUAL)
		DEFINE_MULTIPLE_TOKEN_CASE('&', TOKEN_TYPE_LOGICAL_AND)
		DEFINE_MULTIPLE_TOKENS_END(TOKEN_TYPE_BITWISE_AND);

		DEFINE_MULTIPLE_TOKENS('|');
		DEFINE_MULTIPLE_TOKEN_CASE('=', TOKEN_TYPE_BITWISE_OR_EQUAL)
		DEFINE_MULTIPLE_TOKEN_CASE('|', TOKEN_TYPE_LOGICAL_OR)
		DEFINE_MULTIPLE_TOKENS_END(TOKEN_TYPE_BITWISE_OR);

		DEFINE_MULTIPLE_TOKENS('^');
		DEFINE_MULTIPLE_TOKEN_CASE('=', TOKEN_TYPE_BITWISE_XOR_EQUAL)
		DEFINE_MULTIPLE_TOKENS_END(TOKEN_TYPE_BITWISE_XOR);

		DEFINE_MULTIPLE_TOKENS('~');
		DEFINE_MULTIPLE_TOKEN_CASE('=', TOKEN_TYPE_BITWISE_NOT_EQUAL)
		DEFINE_MULTIPLE_TOKENS_END(TOKEN_TYPE_BITWISE_NOT);

		DEFINE_MULTIPLE_TOKENS('=');
		DEFINE_MULTIPLE_TOKEN_CASE('=', TOKEN_TYPE_EQUAL)
		DEFINE_MULTIPLE_TOKENS_END(TOKEN_TYPE_ASSIGN);

		DEFINE_MULTIPLE_TOKENS('!');
		DEFINE_MULTIPLE_TOKEN_CASE('=', TOKEN_TYPE_NOT_EQUAL)
		DEFINE_MULTIPLE_TOKENS_END(TOKEN_TYPE_LOGICAL_NOT);

		DEFINE_MULTIPLE_TOKENS('<');
		DEFINE_MULTIPLE_TOKEN_CASE('=', TOKEN_TYPE_LESS_EQUAL)
		DEFINE_MULTIPLE_TOKEN_CASE('-', TOKEN_TYPE_LEFT_ARROW)
		DEFINE_MULTIPLE_TOKEN_CASE('<', TOKEN_TYPE_LEFT_SHIFT)
		DEFINE_MULTIPLE_TOKENS_END(TOKEN_TYPE_LESS_THAN);

		DEFINE_MULTIPLE_TOKENS('>');
		DEFINE_MULTIPLE_TOKEN_CASE('=', TOKEN_TYPE_GREATER_EQUAL)
		DEFINE_MULTIPLE_TOKEN_CASE('>', TOKEN_TYPE_RIGHT_SHIFT)
		DEFINE_MULTIPLE_TOKENS_END(TOKEN_TYPE_GREATER_THAN);

	case '"':
		scan_string(token.value.string_value);
		token.type = TOKEN_TYPE_STRING_LITERAL;
		break;

	default:
		if (isdigit(character))
		{
			scan_int(character, &token.value.int_value);
			token.type = TOKEN_TYPE_INT_LITERAL;
			break;
		}

		if (isalpha(character) || character == '_')
		{
			scan_identifier(character, token.value.identifier);

			int token_type = get_keyword(token.value.identifier);
			if (token_type != -1)
			{
				token.type = token_type;
				break;
			}

			token.type = TOKEN_TYPE_IDENTIFIER;
			break;
		}

		fatal("unexpected character\n");
		exit_program();
	}
}

void match_token(int token_type)
{
	if (token.type != token_type)
	{
		fatal("unexpected token\n");
		exit_program();
		
		return;
	}

	next_token();
}

char* match_identifier(void)
{
	char* identifier = duplicate_string(token.value.identifier);
	match_token(TOKEN_TYPE_IDENTIFIER);
	return identifier;
}

void match_left_brace(void)
{
	match_token(TOKEN_TYPE_LEFT_BRACE);
}

void match_right_brace(void)
{
	match_token(TOKEN_TYPE_RIGHT_BRACE);
}
void match_left_parenthesis(void)
{
	match_token(TOKEN_TYPE_LEFT_PARENTHESIS);
}

void match_right_parenthesis(void)
{
	match_token(TOKEN_TYPE_RIGHT_PARENTHESIS);
}

void match_semicolon(void)
{
	match_token(TOKEN_TYPE_SEMICOLON);
}
