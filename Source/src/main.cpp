/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Compiler.hpp"

#include <iostream>
#include <vector>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "hyper: no input files\n";
		return 1;
	}
	
	const std::vector<const char*> files(argv + 1, argv + argc);
	
	Hyper::Compiler compiler(files);
	compiler.compile();

	return 0;
}
