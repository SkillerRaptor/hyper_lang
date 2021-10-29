/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Scanner.hpp"

namespace Hyper
{
	Scanner::Scanner(std::string file_text)
		: m_file_text(std::move(file_text))
	{
	}

	void Scanner::scan_tokens()
	{
		while (!has_reached_end())
		{
			skip_whitespace();

			const std::optional<char> character = advance();
			if (!character.has_value())
			{
				break;
			}

			switch (character.value())
			{
			case ';':
				add_token(";", Token::Type::Semicolon);
				break;
			case '+':
				add_token("+", Token::Type::Plus);
				break;
			case '-':
				add_token("-", Token::Type::Minus);
				break;
			case '*':
				add_token("*", Token::Type::Star);
				break;
			case '/':
				add_token("/", Token::Type::Slash);
				break;
			default:
				if (std::isdigit(character.value()))
				{
					const std::string numeric_literal =
						scan_numeric_literal(character.value());
					add_token(numeric_literal, Token::Type::NumericLiteral);
					break;
				}

				if (std::isalpha(character.value()))
				{
					const std::string identifier = scan_identifier(character.value());
					const std::optional<Token::Type> keyword_type =
						scan_keyword(identifier);

					if (keyword_type.has_value())
					{
						add_token(identifier, keyword_type.value());
						break;
					}

					add_token(identifier, Token::Type::Identifier);
					break;
				}

				break;
			}
		}

		add_token("", Token::Type::Eof);
	}

	std::optional<char> Scanner::advance() noexcept
	{
		if (has_reached_end())
		{
			return std::nullopt;
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

	void Scanner::add_token(const std::string &value, Token::Type token_type)
	{
		SourceLocation source_location = {};
		source_location.line = m_line;
		source_location.column = m_column - value.length() + 1;
		source_location.length = value.length();
		source_location.start = m_position - value.length();

		Token token = {};
		token.value = value;
		token.type = token_type;
		token.location = source_location;

		m_tokens.push_back(token);
	}

	std::string Scanner::scan_numeric_literal(char character)
	{
		std::string numeric_literal;

		std::optional<char> next_character = character;
		while (std::isdigit(next_character.value()))
		{
			numeric_literal += next_character.value();

			next_character = advance();
			if (!next_character.has_value())
			{
				break;
			}
		}

		--m_position;

		return numeric_literal;
	}

	std::string Scanner::scan_identifier(char character)
	{
		std::string identifier;

		std::optional<char> next_character = character;
		while (std::isalpha(next_character.value()) ||
					 std::isdigit(next_character.value()) ||
					 next_character.value() == '_')
		{
			identifier += next_character.value();

			next_character = advance();
			if (!next_character.has_value())
			{
				break;
			}
		}

		--m_position;

		return identifier;
	}

	std::optional<Token::Type> Scanner::scan_keyword(
		const std::string &identifier)
	{
		if (identifier == "print")
		{
			return Token::Type::Print;
		}

		return std::nullopt;
	}

	void Scanner::skip_whitespace() noexcept
	{
		std::optional<char> character = advance();
		if (!character.has_value())
		{
			return;
		}

		while (character.value() == ' ' || character.value() == '\t' ||
					 character.value() == '\n' || character.value() == '\r' ||
					 character.value() == '\f')
		{
			character = advance();
			if (!character.has_value())
			{
				return;
			}
		}

		--m_position;
	}

	bool Scanner::has_reached_end() const noexcept
	{
		return m_position >= m_file_text.length();
	}

	std::vector<Token> Scanner::tokens() const
	{
		return m_tokens;
	}
} // namespace Hyper
