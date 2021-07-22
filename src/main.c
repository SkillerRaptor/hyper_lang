/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <logger.h>
#include <utils.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		fatal("no input files specified\n");
		return 1;
	}

	const char* file_name = argv[1];
	char* file_source = read_file_source(file_name);

	free_file_source(file_source);
}
