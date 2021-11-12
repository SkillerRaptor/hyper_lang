/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <ostream>
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
			PlusEqual,
			Minus,
			MinusEqual,
			Star,
			StarEqual,
			Slash,
			SlashEqual,

			// Comparisons
			Equal,
			NotEqual,
			LessThan,
			GreaterThan,
			LessEqual,
			GreaterEqual,

			// Indicators
			LeftArrow,
			RightArrow,

			LeftCurlyBracket,
			RightCurlyBracket,
			LeftSquareBracket,
			RightSquareBracket,
			LeftRoundBracket,
			RightRoundBracket,

			// Keywords
			Else,
			For,
			Function,
			If,
			Let,
			Mutable,
			Print,
			Return,
			While,

			// Types,
			Bool,
			Int8,
			Int16,
			Int32,
			Int64,
			Uint8,
			Uint16,
			Uint32,
			Uint64,
			ISize,
			USize,
			Void,

			// Literals
			NumericLiteral,
			StringLiteral
		};

		struct SourceLocation
		{
			size_t line = 1;
			size_t column = 1;
			size_t length = 1;
			size_t position = 0;
		};

		std::string value;
		Type type = Type::None;
		SourceLocation location = {};
	};

	std::ostream &operator<<(std::ostream &ostream, const Token::Type &type);
} // namespace Hyper
