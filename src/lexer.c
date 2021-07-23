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

struct token token;

int lexer_init(const char* file_name)
{
	line = 0;
	putback = '\0';
	file = fopen(file_name, "r");

	if (file == NULL)
	{
		fatal("lexer.c: failed to open file %s\n", file_name);
		return 0;
	}

	return 1;
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

static void lexer_scan_int(char character, int* integer)
{
	int i = 0;

	while ((i = chrpos("0123456789", character)) >= 0)
	{
		*integer = *integer * 10 + i;
		character = lexer_next_character();
	}

	putback = character;
}

static int lexer_scan_identifier(char character, char* buffer)
{
	int i = 0;
	while (isalpha(character) || isdigit(character) || character == '_')
	{
		if (i == 128)
		{
			fatal("lexer.c: identifier name is too long\n");
			return 0;
		}

		buffer[i++] = character;
		character = lexer_next_character();
	}

	putback = character;
	buffer[i] = '\0';
	return 1;
}

static int lexer_scan_string(char* buffer)
{
	char character = lexer_next_character();
	for (int i = 0; i < 127; ++i)
	{
		if (character == '"')
		{
			buffer[i] = '\0';
			return i;
		}

		buffer[i] = character;
		character = lexer_next_character();
	}

	fatal("lexer.c: string literal is too long\n");
	return -1;
}

static int lexer_pick_keyword(const char* keyword)
{
	switch (*keyword)
	{
	case 'b':
		if (!strcmp(keyword, "bool"))
		{
			return TOKEN_TYPE_BOOL;
		}

		if (!strcmp(keyword, "break"))
		{
			return TOKEN_TYPE_BREAK;
		}

		if (!strcmp(keyword, "breakll"))
		{
			return TOKEN_TYPE_BREAKALL;
		}
		break;
	case 'c':
		if (!strcmp(keyword, "continue"))
		{
			return TOKEN_TYPE_CONTINUE;
		}
		break;
	case 'd':
		if (!strcmp(keyword, "do"))
		{
			return TOKEN_TYPE_DO;
		}
		break;

		if (!strcmp(keyword, "double"))
		{
			return TOKEN_TYPE_DOUBLE;
		}
	case 'e':
		if (!strcmp(keyword, "else"))
		{
			return TOKEN_TYPE_ELSE;
		}
		break;

		if (!strcmp(keyword, "enum"))
		{
			return TOKEN_TYPE_ENUM;
		}

		if (!strcmp(keyword, "export"))
		{
			return TOKEN_TYPE_EXPORT;
		}
	case 'f':
		if (!strcmp(keyword, "float"))
		{
			return TOKEN_TYPE_FLOAT;
		}

		if (!strcmp(keyword, "for"))
		{
			return TOKEN_TYPE_FOR;
		}

		if (!strcmp(keyword, "function"))
		{
			return TOKEN_TYPE_FUNCTION;
		}
		break;
	case 'i':
		if (!strcmp(keyword, "if"))
		{
			return TOKEN_TYPE_IF;
		}

		if (!strcmp(keyword, "import"))
		{
			return TOKEN_TYPE_IMPORT;
		}

		if (!strcmp(keyword, "int"))
		{
			return TOKEN_TYPE_INT;
		}

		if (!strcmp(keyword, "int8"))
		{
			return TOKEN_TYPE_INT8;
		}

		if (!strcmp(keyword, "int16"))
		{
			return TOKEN_TYPE_INT16;
		}

		if (!strcmp(keyword, "int32"))
		{
			return TOKEN_TYPE_INT32;
		}

		if (!strcmp(keyword, "int64"))
		{
			return TOKEN_TYPE_INT64;
		}
		break;
	case 'm':
		if (!strcmp(keyword, "mutable"))
		{
			return TOKEN_TYPE_MUTABLE;
		}
		break;
	case 'o':
		if (!strcmp(keyword, "of"))
		{
			return TOKEN_TYPE_OF;
		}

		if (!strcmp(keyword, "override"))
		{
			return TOKEN_TYPE_OVERRIDE;
		}
		break;
	case 'p':
		if (!strcmp(keyword, "package"))
		{
			return TOKEN_TYPE_PACKAGE;
		}

		if (!strcmp(keyword, "print"))
		{
			return TOKEN_TYPE_PRINT;
		}
		break;
	case 'r':
		if (!strcmp(keyword, "return"))
		{
			return TOKEN_TYPE_RETURN;
		}
		break;
	case 's':
		if (!strcmp(keyword, "string"))
		{
			return TOKEN_TYPE_STRING;
		}

		if (!strcmp(keyword, "struct"))
		{
			return TOKEN_TYPE_STRUCT;
		}
		break;
	case 'u':
		if (!strcmp(keyword, "uint"))
		{
			return TOKEN_TYPE_UINT;
		}

		if (!strcmp(keyword, "uint8"))
		{
			return TOKEN_TYPE_UINT8;
		}

		if (!strcmp(keyword, "uint16"))
		{
			return TOKEN_TYPE_UINT16;
		}

		if (!strcmp(keyword, "uint32"))
		{
			return TOKEN_TYPE_UINT32;
		}

		if (!strcmp(keyword, "uint64"))
		{
			return TOKEN_TYPE_UINT64;
		}

		if (!strcmp(keyword, "union"))
		{
			return TOKEN_TYPE_UNION;
		}
		break;
	case 'v':
		if (!strcmp(keyword, "virtual"))
		{
			return TOKEN_TYPE_VIRTUAL;
		}
		break;

		if (!strcmp(keyword, "void"))
		{
			return TOKEN_TYPE_VOID;
		}
	case 'w':
		if (!strcmp(keyword, "while"))
		{
			return TOKEN_TYPE_WHILE;
		}
		break;
	default:
		break;
	}

	return -1;
}

int lexer_next_token(struct token* token)
{
	lexer_skip_whitespace();

	memset(&token->value, 0, sizeof(token->value));

	char character = lexer_next_character();
	switch (character)
	{
	case EOF:
		token->type = TOKEN_TYPE_EOF;
		return 0;
	case '+':
		character = lexer_next_character();
		if (character == '+')
		{
			token->type = TOKEN_TYPE_INCREMENT;
			break;
		}

		if (character == '=')
		{
			token->type = TOKEN_TYPE_PLUS_EQUAL;
			break;
		}

		putback = character;
		token->type = TOKEN_TYPE_PLUS;
		break;
	case '-':
		character = lexer_next_character();
		if (character == '+')
		{
			token->type = TOKEN_TYPE_DECREMENT;
			break;
		}

		if (character == '=')
		{
			token->type = TOKEN_TYPE_MINUS_EQUAL;
			break;
		}

		if (character == '>')
		{
			token->type = TOKEN_TYPE_RIGHT_ARROW;
			break;
		}

		putback = character;
		token->type = TOKEN_TYPE_MINUS;
		break;
	case '*':
		character = lexer_next_character();
		if (character == '=')
		{
			token->type = TOKEN_TYPE_STAR_EQUAL;
			break;
		}

		putback = character;
		token->type = TOKEN_TYPE_STAR;
		break;
	case '%':
		character = lexer_next_character();
		if (character == '=')
		{
			token->type = TOKEN_TYPE_MODULAR_EQUAL;
			break;
		}

		putback = character;
		token->type = TOKEN_TYPE_MODULAR;
		break;
	case '&':
		character = lexer_next_character();
		if (character == '=')
		{
			token->type = TOKEN_TYPE_BITWISE_AND_EQUAL;
			break;
		}

		if (character == '&')
		{
			token->type = TOKEN_TYPE_LOGICAL_AND;
			break;
		}

		putback = character;
		token->type = TOKEN_TYPE_BITWISE_AND;
		break;
	case '|':
		character = lexer_next_character();
		if (character == '=')
		{
			token->type = TOKEN_TYPE_BITWISE_OR_EQUAL;
			break;
		}

		if (character == '|')
		{
			token->type = TOKEN_TYPE_LOGICAL_OR;
			break;
		}

		putback = character;
		token->type = TOKEN_TYPE_BITWISE_OR;
		break;
	case '^':
		character = lexer_next_character();
		if (character == '=')
		{
			token->type = TOKEN_TYPE_BITWISE_XOR_EQUAL;
			break;
		}

		putback = character;
		token->type = TOKEN_TYPE_BITWISE_XOR;
		break;
	case '~':
		character = lexer_next_character();
		if (character == '=')
		{
			token->type = TOKEN_TYPE_BITWISE_NOT_EQUAL;
			break;
		}

		putback = character;
		token->type = TOKEN_TYPE_BITWISE_NOT;
		break;
	case '/':
		character = lexer_next_character();
		if (character == '=')
		{
			token->type = TOKEN_TYPE_SLASH_EQUAL;
			break;
		}

		putback = character;
		token->type = TOKEN_TYPE_SLASH;
		break;
	case '=':
		character = lexer_next_character();
		if (character == '=')
		{
			token->type = TOKEN_TYPE_EQUAL;
			break;
		}

		putback = character;
		token->type = TOKEN_TYPE_ASSIGN;
		break;
	case '!':
		character = lexer_next_character();
		if (character == '=')
		{
			token->type = TOKEN_TYPE_NOT_EQUAL;
			break;
		}

		putback = character;
		token->type = TOKEN_TYPE_LOGICAL_NOT;
		break;
	case '<':
		character = lexer_next_character();
		if (character == '=')
		{
			token->type = TOKEN_TYPE_LESS_EQUAL;
			break;
		}

		if (character == '-')
		{
			token->type = TOKEN_TYPE_LEFT_ARROW;
			break;
		}

		if (character == '<')
		{
			token->type = TOKEN_TYPE_LEFT_SHIFT;
			break;
		}

		putback = character;
		token->type = TOKEN_TYPE_LESS_THAN;
		break;
	case '>':
		character = lexer_next_character();
		if (character == '=')
		{
			token->type = TOKEN_TYPE_GREATER_EQUAL;
			break;
		}

		if (character == '>')
		{
			token->type = TOKEN_TYPE_RIGHT_SHIFT;
			break;
		}

		putback = character;
		token->type = TOKEN_TYPE_GREATER_THAN;
		break;
	case ',':
		token->type = TOKEN_TYPE_COMMA;
		break;
	case '.':
		token->type = TOKEN_TYPE_DOT;
		break;
	case ':':
		token->type = TOKEN_TYPE_COLON;
		break;
	case ';':
		token->type = TOKEN_TYPE_SEMICOLON;
		break;
	case '{':
		token->type = TOKEN_TYPE_LEFT_BRACE;
		break;
	case '}':
		token->type = TOKEN_TYPE_RIGHT_BRACE;
		break;
	case '(':
		token->type = TOKEN_TYPE_LEFT_PARENTHESIS;
		break;
	case ')':
		token->type = TOKEN_TYPE_RIGHT_PARENTHESIS;
		break;
	case '[':
		token->type = TOKEN_TYPE_LEFT_BRACKET;
		break;
	case ']':
		token->type = TOKEN_TYPE_RIGHT_BRACKET;
		break;
	case '"':
		if (lexer_scan_string(token->value.string_value) == -1)
		{
			return 0;
		}

		token->type = TOKEN_TYPE_STRING_LITERAL;
		break;
	default:
		if (isdigit(character))
		{
			lexer_scan_int(character, &token->value.int_value);
			token->type = TOKEN_TYPE_INT_LITERAL;
			break;
		}

		if (isalpha(character) || character == '_')
		{
			if (!lexer_scan_identifier(character, token->value.identifier))
			{
				return 0;
			}

			int token_type = lexer_pick_keyword(token->value.identifier);
			if (token_type != -1)
			{
				token->type = token_type;
				break;
			}

			token->type = TOKEN_TYPE_IDENTIFIER;
			break;
		}

		token->type = TOKEN_TYPE_EOF;
		fatal("lexer.c: unexpected character %c\n", character);
		return 0;
	}

	return 1;
}

void lexer_match(int token_type)
{
	if (token.type != token_type)
	{
		fatal("lexer.c: %s unexpected - %s expected\n", token_type_to_string(token.type), token_type_to_string(token_type));
		return;
	}

	lexer_next_token(&token);
}

void lexer_match_identifier(void)
{
	lexer_match(TOKEN_TYPE_IDENTIFIER);
}

void lexer_match_semicolon(void)
{
	lexer_match(TOKEN_TYPE_SEMICOLON);
}
