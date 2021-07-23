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

void generator_generate_code(struct ast* ast);

#endif // HYPERLANG_GENERATOR_H_
