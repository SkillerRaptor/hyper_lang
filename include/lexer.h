/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPERLANG_LEXER_H_
#define HYPERLANG_LEXER_H_

#include <token.h>

extern struct token token;

int lexer_init(const char* source);
void lexer_free(void);

int lexer_next_token(struct token* token);

#endif // HYPERLANG_LEXER_H_
