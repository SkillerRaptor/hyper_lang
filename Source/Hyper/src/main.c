/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "logger.h"
#include "utils.h"

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		hyper_fatal_error("no input files\n");
		terminate_compilation();
	}
	
	(void) argv;
	
	return 0;
}
