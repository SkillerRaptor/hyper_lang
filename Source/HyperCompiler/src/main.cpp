/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "HyperCompiler/BuildOptions.hpp"
#include "HyperCompiler/Compiler.hpp"
#include "HyperCompiler/Utils/PlatformDetection.hpp"

#include <string>
#include <vector>

using namespace HyperCompiler;

int main(int, char**)
{
	setbuf(stdout, nullptr);
	
	unsigned int jobs = 1;

	ArchTarget arch_target;
#if HYPERCOMPILER_ARCH_X86
	arch_target = ArchTarget::x86;
#elif HYPERCOMPILER_ARCH_X86_64
	arch_target = ArchTarget::x86_64;
#endif

	OsTarget os_target;
#if HYPERCOMPILER_PLATFORM_LINUX
	os_target = OsTarget::Linux;
#elif HYPERCOMPILER_PLATFORM_WINDOWS
	os_target = OsTarget::Windows;
#endif

	OptimizationLevel optimization_level = OptimizationLevel::None;
	std::vector<std::string> source_files;
	std::vector<std::string> include_directories;
	std::string output_file = "./a.out";

	// TODO: Implement argument parser
	source_files.emplace_back("./tests/00.hyper");
	
	BuildOptions build_options{};
	build_options.jobs = jobs;
	build_options.arch_target = arch_target;
	build_options.os_target = os_target;
	build_options.optimization_level = optimization_level;
	build_options.source_files = source_files;
	build_options.include_directories = include_directories;
	build_options.output_file = output_file;

	Compiler::compile(build_options);

	return 0;
}
