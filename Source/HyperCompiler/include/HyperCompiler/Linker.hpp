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
	class Linker
	{
	public:
		static void link(const std::string& output_file, const std::vector<std::string>& object_files);
	};
} // namespace HyperCompiler
