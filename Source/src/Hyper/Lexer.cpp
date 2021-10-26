/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Lexer.hpp"

namespace Hyper
{
	Lexer::Lexer(std::string file_name, std::string file_text)
		: m_file_name(std::move(file_name))
		, m_file_text(std::move(file_text))
	{
	}

	Token Lexer::next_token()
	{
		skip_whitespace();

		const char character = advance();
		switch (character)
		{
		case '+':
			return new_token("+", Token::Type::Plus);
		case '-':
			return new_token("-", Token::Type::Minus);
		case '*':
			return new_token("*", Token::Type::Star);
		case '/':
			return new_token("/", Token::Type::Slash);
		default:
			if (m_position >= m_file_text.length())
			{
				return new_token("", Token::Type::Eof);
			}

			if (std::isdigit(character))
			{
				const std::string numeric_literal = scan_numeric_literal(character);
				return new_token(numeric_literal, Token::Type::NumericLiteral);
			}

			break;
		}

		std::abort();
	}

	Token Lexer::new_token(const std::string &value, Token::Type token_type)
	{
		SourceLocation source_location = {};
		source_location.line = m_line;
		source_location.column = m_column - value.length() + 1;
		source_location.length = value.length();
		source_location.start = m_position - value.length();

		Token token = {};
		token.value = value;
		token.type = token_type;
		token.source_location = source_location;

		return token;
	}

	std::string Lexer::scan_numeric_literal(char character)
	{
		std::string numeric_literal;
		numeric_literal += character;

		char next_character = advance();
		while (std::isdigit(next_character))
		{
			numeric_literal += next_character;
			next_character = advance();
		}
		
		revert();

		return numeric_literal;
	}

	void Lexer::skip_whitespace() noexcept
	{
		char character = advance();
		while (character == ' ' || character == '\t' || character == '\n' ||
					 character == '\r' || character == '\f')
		{
			character = advance();
		}

		revert();
	}

	void Lexer::revert() noexcept
	{
		if (m_position <= 0)
		{
			return;
		}

		--m_position;
	}

	char Lexer::advance() noexcept
	{
		if (m_position >= m_file_text.length())
		{
			return '\0';
		}

		const char character = m_file_text[m_position++];
		if (character == '\n')
		{
			++m_line;
			m_column = 0;
		}

		++m_column;

		return character;
	}

	char Lexer::peek() const noexcept
	{
		if (m_position >= m_file_text.length())
		{
			return '\0';
		}

		return m_file_text[m_position];
	}
} // namespace Hyper
