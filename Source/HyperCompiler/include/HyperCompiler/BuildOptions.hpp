/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <string>
#include <vector>

namespace HyperCompiler
{
	enum class ArchTarget : uint8_t
	{
		x86,
		x86_64
	};

	enum class OsTarget : uint8_t
	{
		Linux,
		Windows
	};

	enum class OptimizationLevel : uint8_t
	{
		None = 0,
		Less,
		Default,
		Aggressive
	};

	struct BuildOptions
	{
		unsigned int jobs{ 1 };
		ArchTarget arch_target{ ArchTarget::x86_64 };
		OsTarget os_target{ OsTarget::Linux };
		OptimizationLevel optimization_level{ OptimizationLevel::None };
		std::vector<std::string> source_files;
		std::vector<std::string> include_directories;
		std::string output_file;
	};
} // namespace HyperCompiler
