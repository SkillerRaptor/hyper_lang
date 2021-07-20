/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include <logger.h>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
        fatal("no input files specified\n");
        return 1;
	}
}