/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPERLANG_INTERPRETER_H_
#define HYPERLANG_INTERPRETER_H_

#include <ast.h>

int interpreter_interpret_ast(struct ast* ast);

#endif // HYPERLANG_INTERPRETER_H_
