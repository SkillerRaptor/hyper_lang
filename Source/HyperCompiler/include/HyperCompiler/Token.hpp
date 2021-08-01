/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <fmt/ostream.h>

#include <ostream>
#include <string>

namespace HyperCompiler
{
	struct Token
	{
	public:
		enum class Type
		{
			Eof,

			Plus,
			Minus,
			Star,
			Slash,
			PlusEqual,
			MinusEqual,
			StarEqual,
			SlashEqual,

			Modular,
			ModularEqual,

			Equal,
			NotEqual,
			LessThan,
			GreaterThan,
			LessEqual,
			GreaterEqual,

			LogicalAnd,
			LogicalOr,
			LogicalNot,

			Increment,
			Decrement,

			Assign,
			Identifier,
			Semicolon,
			Colon,
			Comma,
			Dot,

			LeftArrow,
			RightArrow,
			LeftBrace,
			RightBrace,
			LeftParenthesis,
			RightParenthesis,
			LeftBracket,
			RightBracket,
			LeftShift,
			RightShift,

			BitwiseAnd,
			BitwiseOr,
			BitwiseXor,
			BitwiseNot,
			BitwiseAndEqual,
			BitwiseOrEqual,
			BitwiseXorEqual,

			Function,
			Override,
			Virtual,

			If,
			Else,
			Do,
			While,
			For,
			Of,
			Return,

			Break,
			Breakall,
			Continue,

			Import,
			Export,

			Package,
			Mutable,
			Enum,
			Union,
			Struct,

			Bool,
			Char,
			Float,
			Double,
			Int,
			Int8,
			Int16,
			Int32,
			Int64,
			Uint,
			Uint8,
			Uint16,
			Uint32,
			Uint64,
			String,
			Void,

			IntLiteral,
			StringLiteral,

			Print
		};

	public:
		Type type;
		std::string value;
	};
	
	std::ostream& operator<<(std::ostream& ostream, const Token::Type& token_type);
} // namespace HyperCompiler
