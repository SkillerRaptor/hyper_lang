/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Lexer.hpp"

#include "Hyper/Diagnostics.hpp"

namespace Hyper
{
	Lexer::Lexer(std::string file_name, std::string file_text)
		: m_file_name(std::move(file_name))
		, m_file_text(std::move(file_text))
	{
	}

	Token Lexer::scan_next_token()
	{
		skip_whitespace();

		Token token = {};

		const char character = advance();
		switch (character)
		{
		case '+':
			token.value = "+";
			token.type = Token::Type::Plus;
			token.source_location = current_location(1);
			break;
		case '-':
			token.value = "-";
			token.type = Token::Type::Minus;
			token.source_location = current_location(1);
			break;
		case '*':
			token.value = "*";
			token.type = Token::Type::Star;
			token.source_location = current_location(1);
			break;
		case '/':
			token.value = "/";
			token.type = Token::Type::Slash;
			token.source_location = current_location(1);
			break;
		default:
			if (m_position >= m_file_text.length())
			{
				token.value = "";
				token.type = Token::Type::Eof;
				token.source_location = current_location(0);
				break;
			}

			std::abort();
		}

		return token;
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

	SourceLocation Lexer::current_location(const size_t length) const noexcept
	{
		SourceLocation source_location = {};
		source_location.line = m_line;
		source_location.column = m_column;
		source_location.length = length;
		source_location.start = m_position;

		return source_location;
	}
} // namespace Hyper
