/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Compiler.hpp"
#include "Hyper/Logger.hpp"

int main(const int argc, const char **argv)
{
	if (argc < 2)
	{
		Hyper::Logger::log(
			"hyper", Hyper::Logger::Level::Error, "no input files\n");
		return 1;
	}

	Hyper::Compiler compiler(static_cast<size_t>(argc), argv);
	compiler.compile();

	return 0;
}
