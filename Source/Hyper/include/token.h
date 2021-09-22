/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPER_TOKEN_H_
#define HYPER_TOKEN_H_

enum
{
	TOKEN_TYPE_EOF = 0,
	
	TOKEN_TYPE_PLUS,
	TOKEN_TYPE_MINUS,
	TOKEN_TYPE_STAR,
	TOKEN_TYPE_SLASH,
	
	TOKEN_TYPE_NUMERIC_LITERAL
};

struct token
{
	int type;
	char* value;
};

const char* token_type_to_string(int token_type);

#endif //HYPER_TOKEN_H_
