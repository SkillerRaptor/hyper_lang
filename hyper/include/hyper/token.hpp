/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/data_type.hpp"
#include "hyper/source_range.hpp"

#include <string>
#include <string_view>

namespace hyper
{
	class Token
	{
	public:
		enum class Type : uint8_t
		{
			Invalid = 0,

			// NOTE: Special
			Eof,
			Arrow,
			Colon,
			Comma,
			Dot,
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
			BitwiseXorEqual,
			LeftShiftEqual,
			RightShiftEqual,

			// NOTE: Operators (Increment / Decrement)
			Increment,
			Decrement,

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

			QuestionMark,

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
			Extern,
			Export,
			Import,

			// NOTE: Keywords (Definitions)
			As,
			Function,
			Let,
			Mutable,
			Struct,

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
			BoolLiteral,
			FloatingLiteral,
			IntegerLiteral,
			StringLiteral,

			// NOTE: Debug Purpose Only!
			Print,
		};

	public:
		Token() = default;
		Token(std::string value, Type type, SourceRange source_range);

		std::string_view type_string() const noexcept;
		DataType data_type() const noexcept;

		size_t line_number() const noexcept;
		size_t line_column() const noexcept;
		size_t length() const noexcept;

		Position start_position() const noexcept;
		Position end_position() const noexcept;

		std::string value() const;
		Type type() const noexcept;
		SourceRange source_range() const noexcept;

		static constexpr std::string_view token_type_to_string(
			Token::Type token_type) noexcept
		{
			switch (token_type)
			{
			case Token::Type::Eof:
				return "EOF";
			case Token::Type::Arrow:
				return "->";
			case Token::Type::Dot:
				return ".";
			case Token::Type::Colon:
				return ":";
			case Token::Type::Identifier:
				return "identifier";
			case Token::Type::Semicolon:
				return ";";
			case Token::Type::Assign:
				return "=";
			case Token::Type::PlusEqual:
				return "!=";
			case Token::Type::MinusEqual:
				return "-=";
			case Token::Type::StarEqual:
				return "*=";
			case Token::Type::SlashEqual:
				return "/=";
			case Token::Type::PercentEqual:
				return "%=";
			case Token::Type::BitwiseAndEqual:
				return "&=";
			case Token::Type::BitwiseOrEqual:
				return "|=";
			case Token::Type::BitwiseXorEqual:
				return "^=";
			case Token::Type::LeftShiftEqual:
				return "<<=";
			case Token::Type::RightShiftEqual:
				return ">>=";
			case Token::Type::Increment:
				return "++";
			case Token::Type::Decrement:
				return "--";
			case Token::Type::Plus:
				return "+";
			case Token::Type::Minus:
				return "-";
			case Token::Type::Star:
				return "*";
			case Token::Type::Slash:
				return "/";
			case Token::Type::Percent:
				return "%";
			case Token::Type::BitwiseAnd:
				return "&";
			case Token::Type::BitwiseOr:
				return "|";
			case Token::Type::BitwiseNot:
				return "~";
			case Token::Type::BitwiseXor:
				return "^";
			case Token::Type::LeftShift:
				return "<<";
			case Token::Type::RightShift:
				return ">>";
			case Token::Type::LogicalNot:
				return "!";
			case Token::Type::LogicalAnd:
				return "&&";
			case Token::Type::LogicalOr:
				return "||";
			case Token::Type::Equal:
				return "==";
			case Token::Type::NotEqual:
				return "!=";
			case Token::Type::LessThan:
				return "<";
			case Token::Type::GreaterThan:
				return ">";
			case Token::Type::LessEqual:
				return "<=";
			case Token::Type::GreaterEqual:
				return ">=";
			case Token::Type::QuestionMark:
				return "?";
			case Token::Type::CurlyLeftBracket:
				return "{";
			case Token::Type::CurlyRightBracket:
				return "}";
			case Token::Type::SquareLeftBracket:
				return "[";
			case Token::Type::SquareRightBracket:
				return "]";
			case Token::Type::RoundLeftBracket:
				return "(";
			case Token::Type::RoundRightBracket:
				return ")";
			case Token::Type::Break:
				return "break";
			case Token::Type::Else:
				return "else";
			case Token::Type::For:
				return "for";
			case Token::Type::If:
				return "if";
			case Token::Type::Return:
				return "return";
			case Token::Type::While:
				return "while";
			case Token::Type::Export:
				return "export";
			case Token::Type::Import:
				return "import";
			case Token::Type::Function:
				return "fn";
			case Token::Type::Let:
				return "let";
			case Token::Type::Mutable:
				return "mutable";
			case Token::Type::Struct:
				return "struct";
			case Token::Type::Bool:
				return "bool";
			case Token::Type::Int8:
				return "i8";
			case Token::Type::Int16:
				return "";
			case Token::Type::Int32:
				return "i32";
			case Token::Type::Int64:
				return "i64";
			case Token::Type::Uint8:
				return "u8";
			case Token::Type::Uint16:
				return "u16";
			case Token::Type::Uint32:
				return "u32";
			case Token::Type::Uint64:
				return "u64";
			case Token::Type::ISize:
				return "isize";
			case Token::Type::USize:
				return "usize";
			case Token::Type::Float32:
				return "f32";
			case Token::Type::Float64:
				return "f64";
			case Token::Type::String:
				return "string";
			case Token::Type::Void:
				return "void";
			case Token::Type::BoolLiteral:
				return "bool literal";
			case Token::Type::IntegerLiteral:
				return "integer literal";
			case Token::Type::StringLiteral:
				return "string literal";
			default:
				return "";
			}
		}

	private:
		std::string m_value;
		Type m_type = Type::Invalid;
		SourceRange m_source_range = {};
	};
} // namespace hyper
