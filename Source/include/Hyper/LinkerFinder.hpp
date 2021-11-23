/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <optional>
#include <string>

namespace Hyper
{
	class LinkerFinder
	{
	public:
		static std::optional<std::string> find_clang();
		static std::optional<std::string> find_gcc();
		static std::optional<std::string> find_msvc();
	};
} // namespace Hyper
