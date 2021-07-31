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

	enum class SizeOptimization : uint8_t
	{
		None = 0,
		Small,
		Tiny
	};

	enum class PicGeneration : uint8_t
	{
		None = 0,
		Small,
		Big,
	};

	enum class PieGeneration : uint8_t
	{
		None = 0,
		Small,
		Big,
	};

	enum class DebugInfo : uint8_t
	{
		None = 0,
		LineTables,
		Full
	};

	struct BuildOptions
	{
		unsigned int jobs{ 1 };
		ArchTarget arch_target{ ArchTarget::x86_64 };
		OsTarget os_target{ OsTarget::Linux };
		OptimizationLevel optimization_level{ OptimizationLevel::None };
		SizeOptimization size_optimization{ SizeOptimization::None };
		PicGeneration pic_generation{ PicGeneration::None };
		PieGeneration pie_generation{ PieGeneration::None };
		DebugInfo debug_info{ DebugInfo::None };
		std::vector<std::string> source_files;
		std::vector<std::string> include_directories;
	};
} // namespace HyperCompiler
