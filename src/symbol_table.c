/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <logger.h>
#include <symbol_table.h>
#include <utils.h>
#include <string.h>

static int globals = 0;

struct symbol symbol_table[1024] = { 0 };

static int symbol_table_new_global(void)
{
	int i = globals++;

	if (i >= 1024)
	{
		fatal("symbol_table.c: too many global symbols\n");
	}

	return i;
}

int symbol_table_add_global(const char *name)
{
	int i = symbol_table_find_global(name);
	if (i != -1)
	{
		return i;
	}

	i = symbol_table_new_global();
	symbol_table[i].name = strdup(name);

	return i;
}

int symbol_table_find_global(const char *name)
{
	for (int i = 0; i < 1024; ++i)
	{
		if (*name == *symbol_table[i].name && !strcmp(symbol_table[i].name, name))
		{
			return i;
		}
	}
	return -1;
}
