/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/SourceRange.hpp"
#include "Hyper/Type.hpp"

#include <cstdint>
#include <string>

namespace Hyper
{
	struct Symbol
	{
		enum class Kind : uint8_t
		{
			Invalid = 0,

			Function,
			Variable,
		};

		std::string identifier;
		Kind kind = Kind::Invalid;
		Type type = {};
		SourceRange range = {};
	};
} // namespace Hyper
