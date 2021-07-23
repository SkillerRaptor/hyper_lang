/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HYPERLANG_SYMBOL_TABLE_H_
#define HYPERLANG_SYMBOL_TABLE_H_

struct symbol
{
	char* name;
};

extern struct symbol symbol_table[1024];

int symbol_table_add_global(const char* name);
int symbol_table_find_global(const char* name);

#endif // HYPERLANG_SYMBOL_TABLE_H_
