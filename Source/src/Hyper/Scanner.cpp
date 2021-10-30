/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Scanner.hpp"

#include <iostream>

namespace Hyper
{
	Scanner::Scanner(std::string file, std::string text)
		: m_file(std::move(file))
		, m_text(std::move(text))
	{
	}

	std::vector<Token> Scanner::scan_tokens()
	{
		std::vector<Token> tokens = {};
		while (!has_reached_end())
		{
			skip_whitespace();

			char character = advance();
			if (character == '\0')
			{
				break;
			}

			switch (character)
			{
			case ':':
				add_token(tokens, ":", Token::Type::Colon);
				break;
			case ';':
				add_token(tokens, ";", Token::Type::Semicolon);
				break;
			case '+':
				add_token(tokens, "+", Token::Type::Plus);
				break;
			case '-':
				add_token(tokens, "-", Token::Type::Minus);
				break;
			case '*':
				add_token(tokens, "*", Token::Type::Star);
				break;
			case '/':
				add_token(tokens, "/", Token::Type::Slash);
				break;
			case '=':
				if (peek() == '=')
				{
					add_token(tokens, "==", Token::Type::Equal);
					break;
				}

				add_token(tokens, "=", Token::Type::Assign);
				break;
			case '!':
				if (peek() == '=')
				{
					add_token(tokens, "!=", Token::Type::NotEqual);
					break;
				}

				break;
			case '>':
				if (peek() == '=')
				{
					add_token(tokens, ">=", Token::Type::GreaterEqual);
					break;
				}

				add_token(tokens, ">", Token::Type::GreaterThan);
				break;
			case '<':
				if (peek() == '=')
				{
					add_token(tokens, "<=", Token::Type::LessEqual);
					break;
				}

				add_token(tokens, "<", Token::Type::LessThan);
				break;
			default:
				if (std::isdigit(character))
				{
					const std::string numeric_literal = scan_numeric_literal(character);
					add_token(tokens, numeric_literal, Token::Type::NumericLiteral);
					break;
				}

				if (std::isalpha(character))
				{
					const std::string identifier = scan_identifier(character);
					const Token::Type keyword_type = scan_keyword(identifier);
					if (keyword_type == Token::Type::None)
					{
						add_token(tokens, identifier, Token::Type::Identifier);
						break;
					}

					add_token(tokens, identifier, keyword_type);
					break;
				}

				// TODO(SkillerRaptor): Improving error handling
				std::cerr << "hyper: " << m_file << ": unexpected character\n";
				break;
			}
		}

		add_token(tokens, "", Token::Type::Eof);

		return tokens;
	}

	char Scanner::advance() noexcept
	{
		if (has_reached_end())
		{
			return '\0';
		}

		const char character = m_text[m_position++];
		if (character == '\n')
		{
			++m_line;
			m_column = 0;
			return character;
		}

		++m_column;
		return character;
	}

	char Scanner::peek() const noexcept
	{
		if (has_reached_end())
		{
			return '\0';
		}

		return m_text[m_position];
	}

	void Scanner::revert() noexcept
	{
		--m_position;
		--m_column;
	}

	void Scanner::skip_whitespace() noexcept
	{
		if (has_reached_end())
		{
			return;
		}

		char character = advance();
		while (character == ' ' || character == '\t' || character == '\n' ||
					 character == '\r' || character == '\f')
		{
			character = advance();
			if (character == '\0')
			{
				return;
			}
		}

		revert();
	}

	bool Scanner::has_reached_end() const noexcept
	{
		return m_position >= m_text.length();
	}

	void Scanner::add_token(
		std::vector<Token> &tokens,
		const std::string &value,
		Token::Type token_type)
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

		tokens.emplace_back(token);
	}

	std::string Scanner::scan_numeric_literal(char character)
	{
		std::string numeric_literal;

		char next_character = character;
		while (std::isdigit(next_character))
		{
			numeric_literal += next_character;

			next_character = advance();
			if (next_character == '\0')
			{
				return numeric_literal;
			}
		}

		revert();

		return numeric_literal;
	}

	std::string Scanner::scan_identifier(char character)
	{
		std::string identifier;

		char next_character = character;
		while (std::isalpha(next_character) || std::isdigit(next_character) ||
					 next_character == '_')
		{
			identifier += next_character;

			next_character = advance();
			if (next_character == '\0')
			{
				return identifier;
			}
		}

		revert();

		return identifier;
	}

	Token::Type Scanner::scan_keyword(const std::string &identifier)
	{
		if (identifier == "i64")
		{
			return Token::Type::Int64;
		}

		if (identifier == "let")
		{
			return Token::Type::Let;
		}

		if (identifier == "mut")
		{
			return Token::Type::Mutable;
		}

		if (identifier == "print")
		{
			return Token::Type::Print;
		}

		return Token::Type::None;
	}
} // namespace Hyper
