/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Scanner.hpp"

#include "Hyper/Logger.hpp"

namespace Hyper
{
	Scanner::Scanner(std::string file, std::string text, bool debug_mode)
		: m_file(std::move(file))
		, m_text(std::move(text))
		, m_debug_mode(debug_mode)
	{
		register_keywords();
		register_single_char_tokens();
		register_two_char_tokens();

		consume();
	}

	Token Scanner::next_token()
	{
		bool is_eof = m_position >= m_text.length();
		if (!is_eof)
		{
			while (m_current_character == ' ' || m_current_character == '\t' ||
						 m_current_character == '\n' || m_current_character == '\r' ||
						 m_current_character == '\f')
			{
				consume();
			}
		}

		size_t value_start = m_position - 1;
		size_t value_length = 0;
		Token::Type type;
		if (is_eof)
		{
			type = Token::Type::Eof;
		}
		else if (isalpha(m_current_character) || m_current_character == '_')
		{
			type = scan_identifier(value_start, value_length);
		}
		else if (isdigit(m_current_character))
		{
			type = scan_number(value_length);
		}
		else if (m_current_character == '"')
		{
			type = scan_string(value_length);
		}
		else
		{
			type = scan_short_tokens(value_start, value_length);
		}

		m_current_token = {};
		m_current_token.value = m_text.substr(value_start, value_length);
		m_current_token.type = type;
		m_current_token.location.line = m_line_number;
		m_current_token.location.column = m_line_column - value_length + 1;
		m_current_token.location.length = value_length;
		m_current_token.location.position = m_position - value_length;

		debug_scan(m_current_token);

		return m_current_token;
	}

	void Scanner::register_keywords()
	{
		// Built-in types
		m_keywords["bool"] = Token::Type::Bool;
		m_keywords["i8"] = Token::Type::Int8;
		m_keywords["i16"] = Token::Type::Int16;
		m_keywords["i32"] = Token::Type::Int32;
		m_keywords["i64"] = Token::Type::Int64;
		m_keywords["u8"] = Token::Type::Uint8;
		m_keywords["u16"] = Token::Type::Uint16;
		m_keywords["u32"] = Token::Type::Uint32;
		m_keywords["u64"] = Token::Type::Uint64;
		m_keywords["isize"] = Token::Type::ISize;
		m_keywords["usize"] = Token::Type::USize;
		m_keywords["void"] = Token::Type::Void;

		// Control flow keywords
		m_keywords["else"] = Token::Type::Else;
		m_keywords["for"] = Token::Type::For;
		m_keywords["if"] = Token::Type::If;
		m_keywords["return"] = Token::Type::Return;
		m_keywords["while"] = Token::Type::While;

		// Declaration keywords
		m_keywords["function"] = Token::Type::Function;
		m_keywords["let"] = Token::Type::Let;
		m_keywords["mutable"] = Token::Type::Mutable;

		// Temporary built-in function
		m_keywords["print"] = Token::Type::Print;
	}

	void Scanner::register_single_char_tokens()
	{
		// Special symbols
		m_single_char_tokens["="] = Token::Type::Assign;
		m_single_char_tokens[":"] = Token::Type::Colon;
		m_single_char_tokens[";"] = Token::Type::Semicolon;

		// Binary operations
		m_single_char_tokens["+"] = Token::Type::Plus;
		m_single_char_tokens["-"] = Token::Type::Minus;
		m_single_char_tokens["*"] = Token::Type::Star;
		m_single_char_tokens["/"] = Token::Type::Slash;

		// Comparisons
		m_single_char_tokens[">"] = Token::Type::LessThan;
		m_single_char_tokens["<"] = Token::Type::GreaterThan;

		// Brackets
		m_single_char_tokens["{"] = Token::Type::LeftCurlyBracket;
		m_single_char_tokens["}"] = Token::Type::RightCurlyBracket;
		m_single_char_tokens["["] = Token::Type::LeftSquareBracket;
		m_single_char_tokens["]"] = Token::Type::RightSquareBracket;
		m_single_char_tokens["("] = Token::Type::LeftRoundBracket;
		m_single_char_tokens[")"] = Token::Type::RightRoundBracket;
	}

	void Scanner::register_two_char_tokens()
	{
		// Binary assignment
		m_two_char_tokens["+="] = Token::Type::PlusEqual;
		m_two_char_tokens["-="] = Token::Type::MinusEqual;
		m_two_char_tokens["*="] = Token::Type::StarEqual;
		m_two_char_tokens["/="] = Token::Type::SlashEqual;

		// Comparisons
		m_two_char_tokens["=="] = Token::Type::Equal;
		m_two_char_tokens["!="] = Token::Type::NotEqual;
		m_two_char_tokens[">="] = Token::Type::LessEqual;
		m_two_char_tokens["<="] = Token::Type::GreaterEqual;

		// Arrows
		m_two_char_tokens["<-"] = Token::Type::LeftArrow;
		m_two_char_tokens["->"] = Token::Type::RightArrow;
	}

	void Scanner::consume()
	{
		if (m_position >= m_text.length())
		{
			++m_position;
			return;
		}

		if (m_current_character == '\n')
		{
			++m_line_number;
			m_line_column = 0;
		}

		++m_line_column;

		m_current_character = m_text[m_position++];
	}

	Token::Type Scanner::scan_identifier(size_t start, size_t &length)
	{
		do
		{
			++length;
			consume();
		} while (isalnum(m_current_character) || m_current_character == '_');

		const std::string value = m_text.substr(start, length);
		if (m_keywords.find(value) == m_keywords.end())
		{
			return Token::Type::Identifier;
		}

		return m_keywords[value];
	}

	Token::Type Scanner::scan_number(size_t &length)
	{
		// TODO(SkillerRaptor): Scanning after binary, octal or hexadecimal numbers

		do
		{
			++length;
			consume();
		} while (isdigit(m_current_character));

		return Token::Type::NumericLiteral;
	}

	Token::Type Scanner::scan_string(size_t &length)
	{
		consume();

		do
		{
			++length;
			consume();
		} while (isalnum(m_current_character) || m_current_character == '_');

		if (m_current_character != '"')
		{
			// TODO(SkillerRaptor): Handle unclosed string
			std::abort();
		}

		consume();

		length += 2;
		return Token::Type::StringLiteral;
	}

	Token::Type Scanner::scan_short_tokens(size_t start, size_t &length)
	{
		if (m_position < m_text.length())
		{
			const std::string value = m_text.substr(start, 2);
			if (m_two_char_tokens.find(value) != m_two_char_tokens.end())
			{
				consume();
				consume();
				length = 2;
				return m_two_char_tokens[value];
			}
		}

		const std::string value = m_text.substr(start, 1);
		if (m_single_char_tokens.find(value) != m_single_char_tokens.end())
		{
			consume();
			length = 1;
			return m_single_char_tokens[value];
		}

		consume();
		length = 0;
		return Token::Type::None;
	}

	void Scanner::debug_scan(const Token &token) const
	{
		if (!m_debug_mode)
		{
			return;
		}

		Logger::file_info(
			m_file,
			"Scanning {} ({}{}{})\n",
			token.type,
			Formatter::s_color_yellow,
			token.value,
			Formatter::s_color_reset);
	}
} // namespace Hyper
