/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/LinkerFinder.hpp"

namespace Hyper
{
	std::optional<std::string> LinkerFinder::find_clang()
	{
		const bool is_available = std::system("which clang > /dev/null") == 0;
		if (!is_available)
		{
			return std::nullopt;
		}

		return "clang";
	}

	std::optional<std::string> LinkerFinder::find_gcc()
	{
		const bool is_available = std::system("which gcc > /dev/null") == 0;
		if (!is_available)
		{
			return std::nullopt;
		}

		return "gcc";
	}

	std::optional<std::string> LinkerFinder::find_msvc()
	{
		// TODO(SkillerRaptor): Adding implementation to find MSVC
		return std::nullopt;
	}
} // namespace Hyper
