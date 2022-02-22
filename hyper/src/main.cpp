/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/compiler.hpp"
#include "hyper/utilities/args_parser.hpp"

int main(int argc, const char **argv)
{
	std::vector<std::string_view> includes = {};
	std::vector<std::string_view> files = {};

	hyper::ArgsParser args_parser = {};
	args_parser.set_version("Hyper version 1.0.0");
	args_parser.add_option(
		includes, "Include directories", "include", "I", "directories");
	args_parser.add_positional_argument(files, "Files to compile", "files");

	if (!args_parser.parse(argc, argv))
	{
		return EXIT_FAILURE;
	}

	if (files.empty())
	{
		hyper::Logger::error("There was no input files specified\n");
		return EXIT_FAILURE;
	}

	const hyper::Compiler compiler(files);
	return compiler.compile();
}
