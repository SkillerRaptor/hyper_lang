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

			// Special
			Assign,
			Identifier,
			Colon,
			Semicolon,

			// Operators
			Plus,
			Minus,
			Star,
			Slash,
			
			// Comparisons
			Equal,
			NotEqual,
			LessThan,
			GreaterThan,
			LessEqual,
			GreaterEqual,

			// Keywords
			Let,
			Mutable,
			Print,

			// Types,
			Int64,

			// Literals
			NumericLiteral
		};

		std::string value;
		Type type = Type::None;
		SourceLocation location = {};
	};
} // namespace Hyper
