/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <logger.h>
#include <utils.h>
#include <stdio.h>
#include <stdlib.h>

char* read_file_source(const char* file_name)
{
	FILE* file = fopen(file_name, "rb");
	if (file == NULL)
	{
		fatal("logger.c: failed to open %s\n", file_name);
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	size_t length = ftell(file);
	fseek(file, 0, SEEK_SET);

	if (length <= 0)
	{
		fatal("logger.c: file length is less than 0\n");
		fclose(file);

		return NULL;
	}

	if (length > 1073741824)
	{
		fatal("logger.c: file length is exceeding 1073741824\n");
		fclose(file);

		return NULL;
	}

	char* buffer = malloc(length + 1);
	if (buffer == NULL)
	{
		fatal("logger.c: failed to allocate %u bytes\n", length + 1);
		fclose(file);

		return NULL;
	}

	size_t read_length = fread(buffer, 1, length, file);
	if (length != read_length)
	{
		fatal("logger.c: read length is different than the file length\n");
		free(buffer);
		fclose(file);

		return NULL;
	}

	buffer[length] = '\0';
	fclose(file);

	return buffer;
}

void free_file_source(char* buffer)
{
	free(buffer);
}
