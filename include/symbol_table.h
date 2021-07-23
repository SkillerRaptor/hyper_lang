/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPERLANG_SYMBOL_TABLE_H_
#define HYPERLANG_SYMBOL_TABLE_H_

#define SYMBOL_TABLE_LIMIT 1024

struct symbol
{
	char* name;
};

void init_symbols(void);

int add_symbol(const char* name);
int find_symbol(const char* name);

struct symbol* get_symbol(int position);

#endif // HYPERLANG_SYMBOL_TABLE_H_
