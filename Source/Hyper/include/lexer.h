/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPER_LEXER_H_
#define HYPER_LEXER_H_

#include "token.h"

struct lexer
{
	char* file_path;
	char* text;
	
	int text_size;
	int position;
	
	int line;
	int column;
};

int lexer_init(struct lexer** lexer, const char* file_path);
void lexer_free(struct lexer* lexer);

struct token lexer_next_token(struct lexer* lexer);

#endif //HYPER_LEXER_H_
