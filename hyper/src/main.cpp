/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/compiler.hpp"
#include "hyper_utilities/args_parser.hpp"
#include "hyper_utilities/logger.hpp"
#include "hyper_utilities/profiler.hpp"
#include "hyper_utilities/utilities.hpp"

int main(int argc, char **argv)
{
	HYPER_PROFILE_BEGIN("profile.json");

	hyper::Compiler::Options options = {};

	hyper::ArgsParser args_parser = {};
	args_parser.set_version("Hyper version 1.0.0");

	args_parser.add_option(
		options.freestanding,
		"Tells the compiler to use the freestanding mode",
		"freestanding",
		"");

	args_parser.add_option(
		options.linker_script,
		"Tells the compiler to use <file> as linker script",
		"linker-script",
		"l",
		"file");

	args_parser.add_option(
		options.output_directory,
		"Tells the compiler to output the files into <directory>",
		"output-dir",
		"d",
		"directory");

	args_parser.add_option(
		options.output_executable,
		"Tells the compiler to output the executable as <file>",
		"output",
		"o",
		"file");

	args_parser.add_option(
		options.include_directories,
		"Adds <directory> to the compiler's include paths",
		"include",
		"I",
		"directory");

	args_parser.add_positional_argument(
		options.source_files, "Adds <files> to the compiler's target", "files");

	if (!args_parser.parse(argc, argv))
	{
		return EXIT_SUCCESS;
	}

	if (options.source_files.empty())
	{
		hyper::Logger::error("There was no input files specified\n");
		return EXIT_FAILURE;
	}

	const hyper::NonNullUniquePtr<hyper::Compiler> compiler =
		hyper::make_non_null_unqiue<hyper::Compiler>(options);
	if (compiler == nullptr)
	{
		return EXIT_FAILURE;
	}

	const int status = compiler->compile();

	HYPER_PROFILE_END();

	return status;
}
