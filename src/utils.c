/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <utils.h>
#include <stdlib.h>
#include <string.h>

char* strdup(const char* source)
{
	char* destination = malloc(strlen(source) + 1);
	if (destination == NULL)
	{
		return NULL;
	}
	
	strcpy(destination, source);
	return destination;
}
