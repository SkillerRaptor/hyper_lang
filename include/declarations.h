/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPERLANG_DECLARATIONS_H_
#define HYPERLANG_DECLARATIONS_H_

#include "ast.h"

void generate_variable_declaration(void);
struct ast* generate_function_declaration(void);

#endif // HYPERLANG_DECLARATIONS_H_
