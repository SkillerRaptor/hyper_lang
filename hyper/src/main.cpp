/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/compiler.hpp"
#include "hyper/utilities/args_parser.hpp"

int main(int argc, char **argv)
{
	bool freestanding = false;
	std::string_view linker_script = "";
	std::string_view output_file = "";
	std::vector<std::string_view> includes = {};
	std::vector<std::string_view> files = {};

	hyper::ArgsParser args_parser = {};
	args_parser.set_version("Hyper version 1.0.0");
	args_parser.add_option(
		freestanding,
		"Tells the compiler to use the freestanding mode",
		"freestanding",
		"fs");
	args_parser.add_option(
		linker_script,
		"Tells the compiler to use <file> as linker script",
		"linker-script",
		"ls",
		"file");
	args_parser.add_option(
		output_file,
		"Tells the compiler to output into <file>",
		"output",
		"o",
		"file");
	args_parser.add_option(
		includes,
		"Adds <directory> to the compiler's include paths",
		"include",
		"I",
		"directory");
	args_parser.add_positional_argument(
		files, "Adds <file> to the compiler's target", "file");

	if (!args_parser.parse(argc, argv))
	{
		return EXIT_SUCCESS;
	}

	if (files.empty())
	{
		hyper::Logger::error("There was no input files specified\n");
		return EXIT_FAILURE;
	}

	const hyper::Compiler::Arguments arguments = {
		.freestanding = freestanding,
		.linker_script = linker_script,
		.output_file = output_file,
		.includes = includes,
		.files = files,
	};

	const hyper::Compiler compiler(arguments);
	return compiler.compile();
}
