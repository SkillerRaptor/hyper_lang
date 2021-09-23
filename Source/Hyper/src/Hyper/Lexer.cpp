/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Lexer.hpp"

#include "Hyper/Logger.hpp"

#include <cctype>
#include <fstream>
#include <sstream>

namespace Hyper
{
	Lexer::Lexer(std::string t_file)
		: m_file(std::move(t_file))
	{
	}

	auto Lexer::initialize() -> bool
	{
		std::ifstream file_stream(m_file);
		if (!file_stream.is_open())
		{
			Logger::fatal(m_file, "No such file or directory");
			return false;
		}

		std::stringstream string_stream;
		string_stream << file_stream.rdbuf();
		file_stream.close();

		m_text = string_stream.str();

		return true;
	}

	auto Lexer::next_token() -> Token
	{
		skip_next_whitespace();
		
		Token token{};

		char character = next_character();
		switch (character)
		{
		case ':':
			token.value = ":";
			token.type = Token::Type::Colon;
			break;
		case ',':
			token.value = ",";
			token.type = Token::Type::Comma;
			break;
		case '.':
			token.value = ".";
			token.type = Token::Type::Dot;
			break;
		case ';':
			token.value = ";";
			token.type = Token::Type::Semicolon;
			break;
		case '{':
			token.value = "{";
			token.type = Token::Type::LeftBrace;
			break;
		case '}':
			token.value = "}";
			token.type = Token::Type::RightBrace;
			break;
		case '(':
			token.value = "(";
			token.type = Token::Type::LeftParenthesis;
			break;
		case ')':
			token.value = ")";
			token.type = Token::Type::RightParenthesis;
			break;
		case '[':
			token.value = "[";
			token.type = Token::Type::Semicolon;
			break;
		case ']':
			token.value = "]";
			token.type = Token::Type::RightBrace;
			break;
		case '=':
			character = next_character();
			if (character == '=')
			{
				token.value = "==";
				token.type = Token::Type::Equal;
				break;
			}
			
			--m_position;

			token.value = "=";
			token.type = Token::Type::Assign;
			break;
		case '!':
			character = next_character();
			if (character == '=')
			{
				token.value = "!=";
				token.type = Token::Type::NotEqual;
				break;
			}

			--m_position;

			token.value = "!";
			token.type = Token::Type::LogicalNot;
			break;
		case '<':
			character = next_character();
			if (character == '=')
			{
				token.value = "<=";
				token.type = Token::Type::LessEqual;
				break;
			}
			
			if (character == '-')
			{
				token.value = "<-";
				token.type = Token::Type::LeftArrow;
				break;
			}

			if (character == '<')
			{
				token.value = "<<";
				token.type = Token::Type::LeftShift;
				break;
			}

			--m_position;

			token.value = "<";
			token.type = Token::Type::LessThan;
			break;
		case '>':
			character = next_character();
			if (character == '=')
			{
				token.value = ">=";
				token.type = Token::Type::GreaterEqual;
				break;
			}

			if (character == '>')
			{
				token.value = ">>";
				token.type = Token::Type::RightShift;
				break;
			}

			--m_position;

			token.value = ">";
			token.type = Token::Type::GreaterThan;
			break;
		case '+':
			character = next_character();
			if (character == '+')
			{
				token.value = "+";
				token.type = Token::Type::Increment;
				break;
			}
			
			if (character == '=')
			{
				token.value = "+=";
				token.type = Token::Type::PlusEqual;
				break;
			}

			--m_position;

			token.value = "+";
			token.type = Token::Type::Plus;
			break;
		case '-':
			character = next_character();
			if (character == '-')
			{
				token.value = "--";
				token.type = Token::Type::Decrement;
				break;
			}

			if (character == '=')
			{
				token.value = "-=";
				token.type = Token::Type::MinusEqual;
				break;
			}

			if (character == '>')
			{
				token.value = "->";
				token.type = Token::Type::RightArrow;
				break;
			}

			--m_position;

			token.value = "-";
			token.type = Token::Type::Minus;
			break;
		case '*':
			character = next_character();
			if (character == '=')
			{
				token.value = "*=";
				token.type = Token::Type::StarEqual;
				break;
			}

			--m_position;

			token.value = "*";
			token.type = Token::Type::Star;
			break;
		case '/':
			character = next_character();
			if (character == '=')
			{
				token.value = "/=";
				token.type = Token::Type::SlashEqual;
				break;
			}

			--m_position;

			token.value = "/";
			token.type = Token::Type::Slash;
			break;
		case '%':
			character = next_character();
			if (character == '=')
			{
				token.value = "%=";
				token.type = Token::Type::ModularEqual;
				break;
			}

			--m_position;

			token.value = "%";
			token.type = Token::Type::Modular;
			break;
		case '&':
			character = next_character();
			if (character == '=')
			{
				token.value = "&=";
				token.type = Token::Type::BitwiseAndEqual;
				break;
			}
			
			if (character == '&')
			{
				token.value = "&";
				token.type = Token::Type::LogicalAnd;
				break;
			}

			--m_position;

			token.value = "&";
			token.type = Token::Type::BitwiseAnd;
			break;
		case '|':
			character = next_character();
			if (character == '=')
			{
				token.value = "|=";
				token.type = Token::Type::BitwiseOrEqual;
				break;
			}

			if (character == '|')
			{
				token.value = "|";
				token.type = Token::Type::LogicalOr;
				break;
			}

			--m_position;

			token.value = "|";
			token.type = Token::Type::BitwiseOr;
			break;
		case '^':
			character = next_character();
			if (character == '=')
			{
				token.value = "^=";
				token.type = Token::Type::BitwiseXorEqual;
				break;
			}

			--m_position;

			token.value = "^";
			token.type = Token::Type::BitwiseXor;
			break;
		case '~':
			token.value = "~";
			token.type = Token::Type::BitwiseNot;
			break;
		default:
			if (m_position >= m_text.size())
			{
				token.value = "";
				token.type = Token::Type::Eof;
				break;
			}

			if (std::isdigit(character))
			{
				token.value = std::to_string(scan_numeric_literal(character));
				token.type = Token::Type::NumericLiteral;
				break;
			}
			
			if (std::isalpha(character) || character == '_')
			{
				token.value = scan_identifier(character);
				token.type = Token::Type::Identifier;

				Token::Type token_type = to_keyword(token.value);
				if (token_type != Token::Type::Eof)
				{
					token.type = token_type;
				}

				break;
			}

			break;
		}

		return token;
	}

	auto Lexer::next_character() -> char
	{
		if (m_position >= m_text.size())
		{
			return '\0';
		}

		const char character = m_text[m_position++];

		++m_column;

		if (character == '\n')
		{
			++m_line;
			m_column = 1;
		}

		return character;
	}

	auto Lexer::skip_next_whitespace() -> void
	{
		char character;

		do
		{
			character = next_character();
		} while (character == ' ' || character == '\t' || character == '\n' || character == '\r' || character == '\f');

		--m_position;
	}

	auto Lexer::scan_numeric_literal(char character) -> int64_t
	{
		int64_t number = 0;

		int64_t position = character_to_number("0123456789", character);
		while (position >= 0)
		{
			number = number * 10 + position;
			character = next_character();

			position = character_to_number("0123456789", character);
		}

		--m_position;

		return number;
	}

	auto Lexer::character_to_number(const std::string& source, char character) -> int64_t
	{
		for (size_t position = 0; source[position] != '\0'; ++position)
		{
			if (source[position] != character)
			{
				continue;
			}

			return static_cast<int64_t>(position);
		}

		return -1;
	}
	
	auto Lexer::scan_identifier(char character) -> std::string
	{
		std::string string;

		while (isalpha(character) || isdigit(character) || character == '_')
		{
			string += character;
			character = next_character();
		}

		--m_position;

		return string;
	}

	auto Lexer::to_keyword(const std::string& keyword) -> Token::Type
	{
		switch (keyword[0])
		{
		case 'f':
			if (keyword == "fn")
			{
				return Token::Type::Function;
			}
			break;
		case 'r':
			if (keyword == "return")
			{
				return Token::Type::Return;
			}
			break;
		case 'v':
			if (keyword == "void")
			{
				return Token::Type::Void;
			}
			break;
		default:
			break;
		}

		return Token::Type::Eof;
	}
} // namespace Hyper
