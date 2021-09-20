/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "config.h"
#include "logger.h"
#include "utils.h"

#include <string.h>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		hyper_fatal_error("no input files\n");
		terminate_compilation();
	}
	
	if (strcmp(argv[1], "-v") == 0)
	{
		print("Hyper version %s", HYPER_VERSION);
		return 0;
	}
	
	return 0;
}
