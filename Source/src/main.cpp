/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Compiler.hpp"
#include "Hyper/Logger.hpp"

#include <string>
#include <vector>

int main(int argc, const char **argv)
{
	std::setvbuf(stdout, nullptr, _IONBF, 0);

	if (argc < 2)
	{
		Hyper::Logger::error("no input files\n");
		return EXIT_FAILURE;
	}

	const std::vector<std::string> files(argv + 1, argv + argc);
	const Hyper::Compiler compiler(files);
	if (!compiler.compile())
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
