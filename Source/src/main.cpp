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

	// TODO(SkillerRaptor): Adding options parser for compiler settings

	const std::vector<std::string> files(argv + 1, argv + argc);

#if defined(WIN32)
	constexpr Hyper::Target target = Hyper::Target::Windows;
#else
	constexpr Hyper::Target target = Hyper::Target::Linux;
#endif

#if defined(NDEBUG)
	constexpr bool debug_scanner = false;
	constexpr bool debug_parser = false;
	constexpr bool debug_generator = false;
	constexpr bool debug_linker = false;
#else
	constexpr bool debug_scanner = true;
	constexpr bool debug_parser = true;
	constexpr bool debug_generator = true;
	constexpr bool debug_linker = true;
#endif

	const Hyper::Compiler::CreateInfo create_info = {
		.files = files,
		.target = target,
		.debug_scanner = debug_scanner,
		.debug_parser = debug_parser,
		.debug_generator = debug_generator,
		.debug_linker = debug_linker,
	};
	const Hyper::Compiler compiler(create_info);
	if (!compiler.compile())
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
