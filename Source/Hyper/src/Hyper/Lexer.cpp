/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Lexer.hpp"

#include "Hyper/Logger.hpp"

#include <cctype>

namespace Hyper
{
	Lexer::Lexer(std::string file, std::string text)
		: m_file(std::move(file))
		, m_text(std::move(text))
	{
	}

	Token Lexer::next_token()
	{
		advance();
		skip_whitespace();

		const size_t start = m_position;
		const size_t line = m_line;
		const size_t column = m_column;

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

		Token token = {
			.value = value,
			.type = type,
			.pos = start,
			.line = line,
			.column = column,
		};

		Logger::debug("Token '{}' at {}:{}\n", value, line, column);

		return token;
	}

	void Lexer::advance() noexcept
	{
		if (m_position >= m_text.length())
		{
			m_current_char = '\0';
			return;
		}

		if (m_current_char == '\n')
		{
			++m_line;
			m_column = 0;
		}

		++m_column;

		m_current_char = m_text[m_position++];
	}

	char Lexer::peek() const noexcept
	{
		if (m_position + 1 >= m_text.length())
		{
			return '\0';
		}

		return m_text[m_position];
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
		return m_position >= m_text.length();
	}

	std::string Lexer::scan_string()
	{
		std::string string;
		string += m_current_char;

		while (true)
		{
			advance();
			string += m_current_char;

			if (m_current_char == '"')
			{
				break;
			}
		}

		return string;
	}

	std::string Lexer::scan_integer_literal()
	{
		std::string integer_literal;
		integer_literal += m_current_char;

		while (std::isdigit(peek()))
		{
			advance();
			integer_literal += m_current_char;
		}

		return integer_literal;
	}

	std::string Lexer::scan_identifier()
	{
		std::string identifier;
		identifier += m_current_char;

		while (std::isalpha(peek()) || std::isdigit(peek()) || peek() == '_')
		{
			advance();
			identifier += m_current_char;
		}

		return identifier;
	}

	Token::Type Lexer::scan_keyword(const std::string &identifier) const noexcept
	{
		if (identifier == "break")
		{
			return Token::Type::Break;
		}

		if (identifier == "else")
		{
			return Token::Type::Else;
		}

		if (identifier == "for")
		{
			return Token::Type::For;
		}

		if (identifier == "if")
		{
			return Token::Type::If;
		}

		if (identifier == "return")
		{
			return Token::Type::Return;
		}

		if (identifier == "while")
		{
			return Token::Type::While;
		}

		if (identifier == "export")
		{
			return Token::Type::Export;
		}

		if (identifier == "import")
		{
			return Token::Type::Import;
		}

		if (identifier == "fn")
		{
			return Token::Type::Function;
		}

		if (identifier == "let")
		{
			return Token::Type::Let;
		}

		if (identifier == "mutable")
		{
			return Token::Type::Mutable;
		}

		if (identifier == "struct")
		{
			return Token::Type::Struct;
		}

		if (identifier == "bool")
		{
			return Token::Type::Bool;
		}

		if (identifier == "i8")
		{
			return Token::Type::Int8;
		}

		if (identifier == "i16")
		{
			return Token::Type::Int16;
		}

		if (identifier == "i32")
		{
			return Token::Type::Int32;
		}

		if (identifier == "i64")
		{
			return Token::Type::Int64;
		}

		if (identifier == "u8")
		{
			return Token::Type::Uint8;
		}

		if (identifier == "u16")
		{
			return Token::Type::Uint16;
		}

		if (identifier == "u32")
		{
			return Token::Type::Uint32;
		}

		if (identifier == "u64")
		{
			return Token::Type::Uint64;
		}

		if (identifier == "isize")
		{
			return Token::Type::ISize;
		}

		if (identifier == "usize")
		{
			return Token::Type::USize;
		}

		if (identifier == "f32")
		{
			return Token::Type::Float32;
		}

		if (identifier == "f64")
		{
			return Token::Type::Float64;
		}

		if (identifier == "string")
		{
			return Token::Type::String;
		}

		if (identifier == "void")
		{
			return Token::Type::Void;
		}

		if (identifier == "true" || identifier == "false")
		{
			return Token::Type::BoolLiteral;
		}

		return Token::Type::Invalid;
	}
} // namespace Hyper
