/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "HyperCompiler/Linker.hpp"

#include <lld/Common/Driver.h>

namespace HyperCompiler
{
	void Linker::link(const std::string& output_file, const std::vector<std::string>& object_files)
	{
		std::vector<const char*> args;
		args.push_back("-o");
		args.push_back(output_file.c_str());

		for (const std::string& object_file : object_files)
		{
			args.push_back(object_file.c_str());
		}

		std::string output_string{};
		llvm::raw_string_ostream output{ output_string };

		std::string output_error_string{};
		llvm::raw_string_ostream output_error{ output_error_string };

		if (lld::elf::link(args, false, output, output_error))
		{
		}
	}
} // namespace HyperCompiler
