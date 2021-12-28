/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

/*
 * TODO: Adding increment, decrement, floating point literal
 */

#pragma once

#include <string>

namespace Hyper
{
	struct Token
	{
		enum class Type : uint8_t
		{
			Invalid = 0,

			// NOTE: Special
			Eof,
			Arrow,
			Dot,
			Colon,
			Identifier,
			Semicolon,

			// NOTE: Operators (Assignment)
			Assign,
			PlusEqual,
			MinusEqual,
			StarEqual,
			SlashEqual,
			PercentEqual,
			BitwiseAndEqual,
			BitwiseOrEqual,
			BitwiseNotEqual,
			BitwiseXorEqual,
			LeftShiftEqual,
			RightShiftEqual,

			// NOTE: Operators (Arithmetic)
			Plus,
			Minus,
			Star,
			Slash,
			Percent,
			BitwiseAnd,
			BitwiseOr,
			BitwiseNot,
			BitwiseXor,
			LeftShift,
			RightShift,

			// NOTE: Operators (Logical)
			LogicalNot,
			LogicalAnd,
			LogicalOr,

			// NOTE: Operators (Comparison)
			Equal,
			NotEqual,
			LessThan,
			GreaterThan,
			LessEqual,
			GreaterEqual,

			// NOTE: Brackets
			CurlyLeftBracket,
			CurlyRightBracket,
			SquareLeftBracket,
			SquareRightBracket,
			RoundLeftBracket,
			RoundRightBracket,

			// NOTE: Keywords (Control Flow)
			Break,
			Else,
			For,
			If,
			Return,
			While,

			// NOTE: Keywords (Modules)
			Export,
			Import,

			// NOTE: Keywords (Definitions)
			Function,
			Let,
			Mutable,
			Struct,

			// NOTE: Keywords (Literals)
			True,
			False,

			// NOTE: Types
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
			Float32,
			Float64,
			String,
			Void,

			// NOTE: Literals
			IntegerLiteral,
			StringLiteral,
		};

		std::string value;
		Type type = Type::Invalid;
		size_t pos = 0;
		size_t line = 0;
		size_t column = 0;
	};
} // namespace Hyper
