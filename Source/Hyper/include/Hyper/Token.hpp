/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <fmt/ostream.h>

#include <string>

namespace Hyper
{
	struct Token
	{
	public:
		enum class Type
		{
			Eof = 0,

			Assign,
			Identifier,
			Colon,
			Comma,
			Dot,
			Semicolon,
			
			Equal,
			NotEqual,
			LessThan,
			GreaterThan,
			LessEqual,
			GreaterEqual,
			
			Plus,
			PlusEqual,
			Minus,
			MinusEqual,
			Star,
			StarEqual,
			Slash,
			SlashEqual,
			Modular,
			ModularEqual,

			LeftArrow,
			RightArrow,
			LeftBrace,
			RightBrace,
			LeftParenthesis,
			RightParenthesis,
			LeftBracket,
			RightBracket,

			Increment,
			Decrement,

			BitwiseAnd,
			BitwiseOr,
			BitwiseXor,
			BitwiseNot,
			BitwiseAndEqual,
			BitwiseOrEqual,
			BitwiseXorEqual,
			
			LeftShift,
			RightShift,

			LogicalAnd,
			LogicalOr,
			LogicalNot,

			Function,
			
			Return,
			
			Void,
			
			NumericLiteral
		};

	public:
		Type type{ Type::Eof };
		std::string value;
	};

	auto operator<<(std::ostream& ostream, const Token::Type& token_type) -> std::ostream&;
} // namespace Hyper
