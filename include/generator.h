/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPERLANG_GENERATOR_H_
#define HYPERLANG_GENERATOR_H_

#include <ast.h>

void generator_init(const char* file_name);
void generator_free(void);

int generator_generate_ast(struct ast* ast, int reg);
void generator_generate_pre_code(void);
void generator_generate_post_code(void);

int generator_generate_print_int(int value_register);

#endif // HYPERLANG_GENERATOR_H_
