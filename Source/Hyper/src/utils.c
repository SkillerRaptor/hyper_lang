/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "utils.h"

#include "errors.h"
#include "logger.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int hyper_read_file(const char* file_name, char** buffer)
{
	assert(file_name != NULL);
	
	FILE* file = fopen(file_name, "rb");
	if (file == NULL)
	{
		return HYPER_IO_ERROR;
	}
	
	fseek(file, 0, SEEK_END);
	
	long length = ftell(file);
	if (length <= 0 || length >= 1073741824)
	{
		fclose(file);
		return HYPER_OUT_OF_RANGE;
	}
	
	rewind(file);
	
	*buffer = malloc((unsigned long) (length + 1));
	if (*buffer == NULL)
	{
		fclose(file);
		return HYPER_OUT_OF_MEMORY;
	}
	
	fread(*buffer, 1, (unsigned long) length, file);
	
	(*buffer)[length] = '\0';
	fclose(file);
	
	return HYPER_SUCCESS;
}

int hyper_duplicate_string(const char* source, char** destination)
{
	size_t length = strlen(source) + 1;
	
	*destination = malloc(length);
	if (*destination == NULL)
	{
		return HYPER_OUT_OF_MEMORY;
	}
	
	memcpy(*destination, source, length);
	
	return HYPER_SUCCESS;
}

void hyper_terminate_compilation(void)
{
	print("compilation terminated.\n");
	exit(EXIT_FAILURE);
}
