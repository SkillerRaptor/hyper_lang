/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/compiler.hpp"
#include "hyper/logger.hpp"

int main(int argc, const char **argv)
{
	if (argc < 2)
	{
		hyper::Logger::error("there is no input file specified");
		return EXIT_FAILURE;
	}

	// TODO: Adding command line options

	const std::vector<std::string> files(argv + 1, argv + argc);

	const hyper::Compiler compiler(files);
	return compiler.compile();
}
