/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "logger.h"
#include "symbol_table.h"
#include "utils.h"

#include <string.h>

struct symbol_table
{
	struct symbol symbols[SYMBOL_TABLE_LIMIT];
};

static int symbol_count = 0;
static struct symbol_table symbol_table;

void init_symbols(void)
{
	for (int position = 0; position < SYMBOL_TABLE_LIMIT; ++position)
	{
		symbol_table.symbols[position].name = "\0";
	}
}

static int new_symbol(void)
{
	int position = symbol_count++;
	if (position >= 1024)
	{
		fatal("symbol_table.c: too many global symbols\n");
		exit_program();
		
		return -1;
	}

	return position;
}

int add_symbol(const char* name, int primitive_type, int structural_type)
{
	int position = find_symbol(name);
	if (position != -1)
	{
		return position;
	}
	
	position = new_symbol();
	symbol_table.symbols[position].name = duplicate_string(name);
	symbol_table.symbols[position].primitive_type = primitive_type;
	symbol_table.symbols[position].structural_type = structural_type;
	
	return position;
}

int find_symbol(const char* name)
{
	for (int position = 0; position < SYMBOL_TABLE_LIMIT; ++position)
	{
		if (strcmp(symbol_table.symbols[position].name, name) != 0)
		{
			continue;
		}
		
		return position;
	}

	return -1;
}

struct symbol* get_symbol(int position)
{
	if (position >= SYMBOL_TABLE_LIMIT || position < 0)
	{
		fatal("symbol position is out of range: %i\n", position);
		exit_program();
		
		return NULL;
	}
	
	return &symbol_table.symbols[position];
}
