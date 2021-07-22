/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPERLANG_EXPRESSIONS_H_
#define HYPERLANG_EXPRESSIONS_H_

#include <ast.h>

int expressions_arithmetic_operation(int token_type);

struct ast* ast_primary(void);
struct ast* ast_binary_expression(void);

#endif // HYPERLANG_EXPRESSIONS_H_
