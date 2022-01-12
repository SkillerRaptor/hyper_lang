/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Lexer.hpp"

#include "Hyper/Diagnostics.hpp"
#include "Hyper/Hasher.hpp"

#include <cctype>

namespace Hyper
{
	Lexer::Lexer(Diagnostics &diagnostics, std::string text)
		: m_diagnostics(diagnostics)
		, m_text(std::move(text))
	{
	}

	Token Lexer::next_token()
	{
		advance();
		skip_whitespace();

		const Position start = {
			.line = m_line,
			.column = m_column,
		};

		std::string value;
		Token::Type type = Token::Type::Invalid;
		switch (m_current_char)
		{
		case '.':
			value = ".";
			type = Token::Type::Dot;
			break;
		case ':':
			value = ":";
			type = Token::Type::Colon;
			break;
		case ';':
			value = ";";
			type = Token::Type::Semicolon;
			break;
		case '=':
			if (peek() == '=')
			{
				advance();
				value = "==";
				type = Token::Type::Equal;
				break;
			}

			value = "=";
			type = Token::Type::Assign;
			break;
		case '+':
			if (peek() == '+')
			{
				advance();
				value = "++";
				type = Token::Type::Increment;
				break;
			}

			if (peek() == '=')
			{
				advance();
				value = "+=";
				type = Token::Type::PlusEqual;
				break;
			}

			value = "+";
			type = Token::Type::Plus;
			break;
		case '-':
			if (peek() == '-')
			{
				advance();
				value = "--";
				type = Token::Type::Decrement;
				break;
			}

			if (peek() == '=')
			{
				advance();
				value = "-=";
				type = Token::Type::MinusEqual;
				break;
			}

			if (peek() == '>')
			{
				advance();
				value = "->";
				type = Token::Type::Arrow;
				break;
			}

			value = "-";
			type = Token::Type::Minus;
			break;
		case '*':
			if (peek() == '=')
			{
				advance();
				value = "*=";
				type = Token::Type::StarEqual;
				break;
			}

			value = "*";
			type = Token::Type::Star;
			break;
		case '/':
			if (peek() == '/')
			{
				return scan_comment();
			}

			if (peek() == '*')
			{
				return scan_block_comment();
			}

			if (peek() == '=')
			{
				advance();
				value = "/=";
				type = Token::Type::SlashEqual;
				break;
			}

			value = "/";
			type = Token::Type::Slash;
			break;
		case '%':
			if (peek() == '=')
			{
				advance();
				value = "%=";
				type = Token::Type::PercentEqual;
				break;
			}

			value = "%";
			type = Token::Type::Percent;
			break;
		case '&':
			if (peek() == '&')
			{
				advance();
				value = "&&";
				type = Token::Type::LogicalAnd;
				break;
			}

			if (peek() == '=')
			{
				advance();
				value = "&=";
				type = Token::Type::BitwiseAndEqual;
				break;
			}

			value = "&";
			type = Token::Type::BitwiseAnd;
			break;
		case '|':
			if (peek() == '|')
			{
				advance();
				value = "||";
				type = Token::Type::LogicalOr;
				break;
			}

			if (peek() == '=')
			{
				advance();
				value = "|=";
				type = Token::Type::BitwiseOrEqual;
				break;
			}

			value = "|";
			type = Token::Type::BitwiseOr;
			break;
		case '~':
			value = "~";
			type = Token::Type::BitwiseNot;
			break;
		case '^':
			if (peek() == '=')
			{
				advance();
				value = "^=";
				type = Token::Type::BitwiseXorEqual;
				break;
			}

			value = "^";
			type = Token::Type::BitwiseXor;
			break;
		case '<':
			if (peek() == '<')
			{
				advance();
				if (peek() == '=')
				{
					advance();
					value = "<<=";
					type = Token::Type::LeftShiftEqual;
					break;
				}

				value = "<<";
				type = Token::Type::LeftShift;
				break;
			}

			if (peek() == '=')
			{
				advance();
				value = "<=";
				type = Token::Type::LessEqual;
				break;
			}

			value = "<";
			type = Token::Type::LessThan;
			break;
		case '>':
			if (peek() == '>')
			{
				advance();
				if (peek() == '=')
				{
					advance();
					value = ">>=";
					type = Token::Type::RightShiftEqual;
					break;
				}

				value = ">>";
				type = Token::Type::RightShift;
				break;
			}

			if (peek() == '=')
			{
				advance();
				value = ">=";
				type = Token::Type::GreaterEqual;
				break;
			}

			value = ">";
			type = Token::Type::GreaterThan;
			break;
		case '?':
			value = "?";
			type = Token::Type::QuestionMark;
			break;
		case '!':
			if (peek() == '=')
			{
				advance();
				value = "!=";
				type = Token::Type::NotEqual;
				break;
			}

			value = "!";
			type = Token::Type::LogicalNot;
			break;
		case '{':
			value = "{";
			type = Token::Type::CurlyLeftBracket;
			break;
		case '}':
			value = "}";
			type = Token::Type::CurlyRightBracket;
			break;
		case '[':
			value = "[";
			type = Token::Type::SquareLeftBracket;
			break;
		case ']':
			value = "]";
			type = Token::Type::SquareRightBracket;
			break;
		case '(':
			value = "(";
			type = Token::Type::RoundLeftBracket;
			break;
		case ')':
			value = ")";
			type = Token::Type::RoundRightBracket;
			break;
		case '"':
			value = scan_string();
			type = Token::Type::StringLiteral;
			break;
		default:
			if (has_reached_end())
			{
				value = "";
				type = Token::Type::Eof;
				break;
			}

			if (std::isdigit(m_current_char))
			{
				value = scan_integer_literal();
				type = Token::Type::IntegerLiteral;
				break;
			}

			if (std::isalpha(m_current_char))
			{
				value = scan_identifier();
				type = Token::Type::Identifier;

				const Token::Type keyword_type = scan_keyword(value);
				if (keyword_type != Token::Type::Invalid)
				{
					type = keyword_type;
				}

				break;
			}

			value = m_current_char;
			type = Token::Type::Invalid;

			// TODO: Handle unexpected character

			break;
		}

		const SourceRange range = {
				.start = start,
				.end = {
					.line = m_line,
					.column = m_column,
				},
			};

		return {
			.value = value,
			.type = type,
			.range = range,
		};
	}

	void Lexer::advance() noexcept
	{
		if (has_reached_end())
		{
			m_current_char = '\0';
			return;
		}

		if (m_current_char == '\n')
		{
			++m_line;
			m_column = 0;
		}

		if (m_current_char == '\t')
		{
			++m_column;
		}

		++m_column;

		m_current_char = m_text[m_index++];
	}

	char Lexer::peek() const noexcept
	{
		if (has_reached_end())
		{
			return '\0';
		}

		return m_text[m_index];
	}

	void Lexer::skip_whitespace() noexcept
	{
		while (m_current_char == ' ' || m_current_char == '\t' ||
					 m_current_char == '\n' || m_current_char == '\r' ||
					 m_current_char == '\f')
		{
			advance();
		}
	}

	bool Lexer::has_reached_end() const noexcept
	{
		return m_index >= m_text.length();
	}

	Token Lexer::scan_comment() noexcept
	{
		advance();
		while (peek() != '\n')
		{
			advance();
		}

		return next_token();
	}

	Token Lexer::scan_block_comment() noexcept
	{
		const Position start = {
			.line = m_line,
			.column = m_column,
		};

		while (true)
		{
			advance();

			if (peek() == '*')
			{
				advance();
				if (peek() == '/')
				{
					advance();
					break;
				}
			}

			if (has_reached_end())
			{
				const SourceRange source_range = {
					.start = start,
					.end ={
						.line = m_line,
						.column = m_column - 1,
					},
				};

				m_diagnostics.error(source_range, "unterminated block comment");
			}
		}

		return next_token();
	}

	std::string Lexer::scan_string()
	{
		std::string string(1, m_current_char);

		const Position start = {
			.line = m_line,
			.column = m_column,
		};

		do
		{
			advance();
			string += m_current_char;
		} while (m_current_char != '"' && !has_reached_end());

		if (has_reached_end())
		{
			const SourceRange source_range = {
				.start = start,
				.end = {
					.line = m_line,
					.column = m_column - 1,
				},
			};

			m_diagnostics.error(source_range, "unterminated double quote string");
		}

		return string;
	}

	std::string Lexer::scan_integer_literal()
	{
		std::string string(1, m_current_char);
		while (std::isdigit(peek()))
		{
			advance();
			string += m_current_char;
		}

		return string;
	}

	std::string Lexer::scan_identifier()
	{
		std::string string(1, m_current_char);
		while (std::isalpha(peek()) || std::isdigit(peek()) || peek() == '_')
		{
			advance();
			string += m_current_char;
		}

		return string;
	}

	Token::Type Lexer::scan_keyword(std::string_view identifier) const noexcept
	{
		switch (Utils::hash_string(identifier))
		{
		case Utils::hash_string<"as">():
			return Token::Type::As;
		case Utils::hash_string<"break">():
			return Token::Type::Break;
		case Utils::hash_string<"else">():
			return Token::Type::Else;
		case Utils::hash_string<"for">():
			return Token::Type::For;
		case Utils::hash_string<"if">():
			return Token::Type::If;
		case Utils::hash_string<"return">():
			return Token::Type::Return;
		case Utils::hash_string<"while">():
			return Token::Type::While;
		case Utils::hash_string<"export">():
			return Token::Type::Export;
		case Utils::hash_string<"import">():
			return Token::Type::Import;
		case Utils::hash_string<"fn">():
			return Token::Type::Function;
		case Utils::hash_string<"let">():
			return Token::Type::Let;
		case Utils::hash_string<"mutable">():
			return Token::Type::Mutable;
		case Utils::hash_string<"struct">():
			return Token::Type::Struct;
		case Utils::hash_string<"bool">():
			return Token::Type::Bool;
		case Utils::hash_string<"i8">():
			return Token::Type::Int8;
		case Utils::hash_string<"i16">():
			return Token::Type::Int16;
		case Utils::hash_string<"i32">():
			return Token::Type::Int32;
		case Utils::hash_string<"i64">():
			return Token::Type::Int64;
		case Utils::hash_string<"u8">():
			return Token::Type::Uint8;
		case Utils::hash_string<"u16">():
			return Token::Type::Uint16;
		case Utils::hash_string<"u32">():
			return Token::Type::Uint32;
		case Utils::hash_string<"u64">():
			return Token::Type::Uint64;
		case Utils::hash_string<"isize">():
			return Token::Type::ISize;
		case Utils::hash_string<"usize">():
			return Token::Type::USize;
		case Utils::hash_string<"f32">():
			return Token::Type::Float32;
		case Utils::hash_string<"f64">():
			return Token::Type::Float64;
		case Utils::hash_string<"string">():
			return Token::Type::String;
		case Utils::hash_string<"void">():
			return Token::Type::Void;
		case Utils::hash_string<"true">():
		case Utils::hash_string<"false">():
			return Token::Type::BoolLiteral;
		default:
			return Token::Type::Invalid;
		}
	}
} // namespace Hyper
