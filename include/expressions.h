/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPERLANG_EXPRESSIONS_H_
#define HYPERLANG_EXPRESSIONS_H_

#include "ast.h"

struct ast* generate_binary_expression(int precedence);

#endif // HYPERLANG_EXPRESSIONS_H_
