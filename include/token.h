/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPERLANG_TOKEN_H_
#define HYPERLANG_TOKEN_H_

enum
{
	TOKEN_TYPE_EOF,

	TOKEN_TYPE_PLUS,
	TOKEN_TYPE_MINUS,
	TOKEN_TYPE_STAR,
	TOKEN_TYPE_SLASH,

	TOKEN_TYPE_PLUS_EQUAL,
	TOKEN_TYPE_MINUS_EQUAL,
	TOKEN_TYPE_STAR_EQUAL,
	TOKEN_TYPE_SLASH_EQUAL,

	TOKEN_TYPE_MODULAR,
	TOKEN_TYPE_MODULAR_EQUAL,

	TOKEN_TYPE_EQUAL,
	TOKEN_TYPE_NOT_EQUAL,
	TOKEN_TYPE_LESS_THAN,
	TOKEN_TYPE_GREATER_THAN,
	TOKEN_TYPE_LESS_EQUAL,
	TOKEN_TYPE_GREATER_EQUAL,

	TOKEN_TYPE_LOGICAL_AND,
	TOKEN_TYPE_LOGICAL_OR,
	TOKEN_TYPE_LOGICAL_NOT,

	TOKEN_TYPE_INCREMENT,
	TOKEN_TYPE_DECREMENT,

	TOKEN_TYPE_SEMICOLON,
	TOKEN_TYPE_ASSIGN,
	TOKEN_TYPE_IDENTIFIER,

	TOKEN_TYPE_COLON,
	TOKEN_TYPE_COMMA,
	TOKEN_TYPE_DOT,

	TOKEN_TYPE_LEFT_ARROW,
	TOKEN_TYPE_RIGHT_ARROW,

	TOKEN_TYPE_LEFT_BRACE,
	TOKEN_TYPE_RIGHT_BRACE,
	TOKEN_TYPE_LEFT_PARENTHESIS,
	TOKEN_TYPE_RIGHT_PARENTHESIS,
	TOKEN_TYPE_LEFT_BRACKET,
	TOKEN_TYPE_RIGHT_BRACKET,

	TOKEN_TYPE_LEFT_SHIFT,
	TOKEN_TYPE_RIGHT_SHIFT,

	TOKEN_TYPE_BITWISE_AND,
	TOKEN_TYPE_BITWISE_OR,
	TOKEN_TYPE_BITWISE_XOR,
	TOKEN_TYPE_BITWISE_NOT,

	TOKEN_TYPE_BITWISE_AND_EQUAL,
	TOKEN_TYPE_BITWISE_OR_EQUAL,
	TOKEN_TYPE_BITWISE_XOR_EQUAL,
	TOKEN_TYPE_BITWISE_NOT_EQUAL,

	TOKEN_TYPE_FUNCTION,
	TOKEN_TYPE_VIRTUAL,
	TOKEN_TYPE_OVERRIDE,

	TOKEN_TYPE_IF,
	TOKEN_TYPE_ELSE,
	TOKEN_TYPE_DO,
	TOKEN_TYPE_WHILE,
	TOKEN_TYPE_FOR,
	TOKEN_TYPE_OF,
	TOKEN_TYPE_RETURN,

	TOKEN_TYPE_BREAK,
	TOKEN_TYPE_BREAKALL,
	TOKEN_TYPE_CONTINUE,

	TOKEN_TYPE_IMPORT,
	TOKEN_TYPE_EXPORT,

	TOKEN_TYPE_PACKAGE,
	TOKEN_TYPE_MUTABLE,
	TOKEN_TYPE_ENUM,
	TOKEN_TYPE_UNION,
	TOKEN_TYPE_STRUCT,

	TOKEN_TYPE_VOID,
	TOKEN_TYPE_BOOL,
	TOKEN_TYPE_FLOAT,
	TOKEN_TYPE_DOUBLE,
	TOKEN_TYPE_INT,
	TOKEN_TYPE_INT8,
	TOKEN_TYPE_INT16,
	TOKEN_TYPE_INT32,
	TOKEN_TYPE_INT64,
	TOKEN_TYPE_UINT,
	TOKEN_TYPE_UINT8,
	TOKEN_TYPE_UINT16,
	TOKEN_TYPE_UINT32,
	TOKEN_TYPE_UINT64,
	TOKEN_TYPE_STRING,

	TOKEN_TYPE_INT_LITERAL,
	TOKEN_TYPE_STRING_LITERAL,

	/* Testing */
	TOKEN_TYPE_PRINT,
	/* Testing End */
};

struct token
{
	int type;

	union
	{
		int int_value;
		char string_value[128];
		char identifier[128];
	} value;
};

const char* token_type_to_string(int type);

#endif // HYPERLANG_TOKEN_H_