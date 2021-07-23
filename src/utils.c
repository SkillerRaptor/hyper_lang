/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "utils.h"

#include "logger.h"

#include <stdlib.h>
#include <string.h>

char* duplicate_string(const char* source)
{
	char* destination = malloc(strlen(source) + 1);
	if (destination == NULL)
	{
		fatal("out of memory\n");
		exit_program();
		
		return NULL;
	}
	
	strcpy(destination, source);
	return destination;
}

int character_position(const char* string, char character)
{
	for (int position = 0; string[position] != '\0'; ++position)
	{
		if (string[position] != character)
		{
			continue;
		}
		
		return position;
	}
	
	return -1;
}

void exit_program(void)
{
	fatal("compilation failed\n");
	exit(1);
}
