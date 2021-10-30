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
			
			// Brackets
			LeftBrace,
			RightBrace,
			LeftParenthesis,
			RightParenthesis,
			LeftBracket,
			RightBracket,
			
			// Comparisons
			Equal,
			NotEqual,
			LessThan,
			GreaterThan,
			LessEqual,
			GreaterEqual,

			// Keywords
			Else,
			If,
			Let,
			Mutable,
			Print,
			While,

			// Types,
			Int8,
			Int16,
			Int32,
			Int64,
			Uint8,
			Uint16,
			Uint32,
			Uint64,

			// Literals
			NumericLiteral
		};

		std::string value;
		Type type = Type::None;
		SourceLocation location = {};
	};
} // namespace Hyper
