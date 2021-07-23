/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPERLANG_GENERATOR_H_
#define HYPERLANG_GENERATOR_H_

#include "ast.h"

void init_generator(const char* file_name);
void free_generator(void);

int generate_print_register(int value_register);

void generate_pre_code(void);
void generate_post_code(void);

int generate_ast(struct ast* ast, int reg);

#endif // HYPERLANG_GENERATOR_H_
