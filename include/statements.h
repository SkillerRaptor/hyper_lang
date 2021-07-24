/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPERLANG_STATEMENTS_H_
#define HYPERLANG_STATEMENTS_H_

struct ast* generate_assignment_statement(void);
struct ast* generate_if_statement(void);
struct ast* generate_print_statement(void);

struct ast* generate_compound_statement(void);

#endif // HYPERLANG_STATEMENTS_H_
