/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPERLANG_LEXER_H_
#define HYPERLANG_LEXER_H_

#include "token.h"

extern struct token token;

void init_lexer(const char* source);
void free_lexer(void);

void next_token(void);

void match_token(int token_type);

char* match_identifier(void);

void match_left_brace(void);
void match_right_brace(void);
void match_left_parenthesis(void);
void match_right_parenthesis(void);

void match_semicolon(void);

#endif // HYPERLANG_LEXER_H_
