/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/SourceLocation.hpp"

#include <string>

namespace Hyper
{
	struct Token
	{
		enum class Type : unsigned char
		{
			None = 0,

			Eof,

			Plus,
			Minus,
			Star,
			Slash,

			NumericLiteral
		};

		std::string value;
		Type type = Type::None;
		SourceLocation location = {};
	};
} // namespace Hyper
