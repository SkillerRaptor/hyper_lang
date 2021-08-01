/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "HyperCompiler/Lexer.hpp"

#include "HyperCompiler/Logger.hpp"
#include "HyperCompiler/Utils/Utilities.hpp"

#include <cctype>
#include <filesystem>

namespace HyperCompiler
{
	void Lexer::initialize(const std::string& file_name, const std::string& source)
	{
		m_file_name = file_name;
		m_source = source;
		m_line = 1;
		m_line_position = 0;
		m_current_position = 0;
	}

	void Lexer::next_token()
	{
		skip_whitespace();

		char character = next_character();
		switch (character)
		{
		case ',':
			m_current_token.value = ",";
			m_current_token.type = Token::Type::Comma;
			break;
		case '.':
			m_current_token.value = ".";
			m_current_token.type = Token::Type::Dot;
			break;
		case ':':
			m_current_token.value = ":";
			m_current_token.type = Token::Type::Colon;
			break;
		case ';':
			m_current_token.value = ";";
			m_current_token.type = Token::Type::Semicolon;
			break;
		case '{':
			m_current_token.value = "{";
			m_current_token.type = Token::Type::LeftBrace;
			break;
		case '}':
			m_current_token.value = "}";
			m_current_token.type = Token::Type::RightBrace;
			break;
		case '(':
			m_current_token.value = "(";
			m_current_token.type = Token::Type::LeftParenthesis;
			break;
		case ')':
			m_current_token.value = ")";
			m_current_token.type = Token::Type::RightParenthesis;
			break;
		case '[':
			m_current_token.value = "[";
			m_current_token.type = Token::Type::Semicolon;
			break;
		case ']':
			m_current_token.value = "]";
			m_current_token.type = Token::Type::RightBrace;
			break;

		case '+':
			character = next_character();
			if (character == '+')
			{
				m_current_token.value = "+";
				m_current_token.type = Token::Type::Increment;
				break;
			}

			if (character == '=')
			{
				m_current_token.value = "+=";
				m_current_token.type = Token::Type::PlusEqual;
				break;
			}

			--m_current_position;

			m_current_token.value = "+";
			m_current_token.type = Token::Type::Plus;
			break;

		case '-':
			character = next_character();
			if (character == '-')
			{
				m_current_token.value = "--";
				m_current_token.type = Token::Type::Decrement;
				break;
			}

			if (character == '=')
			{
				m_current_token.value = "-=";
				m_current_token.type = Token::Type::MinusEqual;
				break;
			}

			if (character == '>')
			{
				m_current_token.value = ">";
				m_current_token.type = Token::Type::RightArrow;
				break;
			}

			--m_current_position;

			m_current_token.value = "-";
			m_current_token.type = Token::Type::Minus;
			break;

		case '*':
			character = next_character();
			if (character == '=')
			{
				m_current_token.value = "*=";
				m_current_token.type = Token::Type::StarEqual;
				break;
			}

			--m_current_position;

			m_current_token.value = "*";
			m_current_token.type = Token::Type::Star;
			break;

		case '/':
			character = next_character();
			if (character == '=')
			{
				m_current_token.value = "/=";
				m_current_token.type = Token::Type::SlashEqual;
				break;
			}

			--m_current_position;

			m_current_token.value = "/";
			m_current_token.type = Token::Type::Slash;
			break;

		case '%':
			character = next_character();
			if (character == '=')
			{
				m_current_token.value = "%=";
				m_current_token.type = Token::Type::ModularEqual;
				break;
			}

			--m_current_position;

			m_current_token.value = "%";
			m_current_token.type = Token::Type::Modular;
			break;

		case '&':
			character = next_character();
			if (character == '=')
			{
				m_current_token.value = "&=";
				m_current_token.type = Token::Type::BitwiseAndEqual;
				break;
			}

			if (character == '&')
			{
				m_current_token.value = "&";
				m_current_token.type = Token::Type::LogicalAnd;
				break;
			}

			--m_current_position;

			m_current_token.value = "&";
			m_current_token.type = Token::Type::BitwiseAnd;
			break;

		case '|':
			character = next_character();
			if (character == '=')
			{
				m_current_token.value = "|=";
				m_current_token.type = Token::Type::BitwiseOrEqual;
				break;
			}

			if (character == '|')
			{
				m_current_token.value = "|";
				m_current_token.type = Token::Type::LogicalOr;
				break;
			}

			--m_current_position;

			m_current_token.value = "|";
			m_current_token.type = Token::Type::BitwiseOr;
			break;

		case '^':
			character = next_character();
			if (character == '=')
			{
				m_current_token.value = "^=";
				m_current_token.type = Token::Type::BitwiseXorEqual;
				break;
			}

			--m_current_position;

			m_current_token.value = "^";
			m_current_token.type = Token::Type::BitwiseXor;
			break;

		case '~':
			m_current_token.value = "~";
			m_current_token.type = Token::Type::BitwiseNot;
			break;

		case '=':
			character = next_character();
			if (character == '=')
			{
				m_current_token.value = "==";
				m_current_token.type = Token::Type::Equal;
				break;
			}

			--m_current_position;

			m_current_token.value = "=";
			m_current_token.type = Token::Type::Assign;
			break;

		case '!':
			character = next_character();
			if (character == '=')
			{
				m_current_token.value = "!=";
				m_current_token.type = Token::Type::NotEqual;
				break;
			}

			--m_current_position;

			m_current_token.value = "!";
			m_current_token.type = Token::Type::LogicalNot;
			break;

		case '<':
			character = next_character();
			if (character == '=')
			{
				m_current_token.value = "<=";
				m_current_token.type = Token::Type::LessEqual;
				break;
			}

			if (character == '-')
			{
				m_current_token.value = "<-";
				m_current_token.type = Token::Type::LeftArrow;
				break;
			}

			if (character == '<')
			{
				m_current_token.value = "<<";
				m_current_token.type = Token::Type::LeftShift;
				break;
			}

			--m_current_position;

			m_current_token.value = "<";
			m_current_token.type = Token::Type::LessThan;
			break;

		case '>':
			character = next_character();
			if (character == '=')
			{
				m_current_token.value = ">=";
				m_current_token.type = Token::Type::GreaterEqual;
				break;
			}

			if (character == '>')
			{
				m_current_token.value = ">>";
				m_current_token.type = Token::Type::RightShift;
				break;
			}

			--m_current_position;

			m_current_token.value = ">";
			m_current_token.type = Token::Type::GreaterThan;
			break;

		case '"':
			m_current_token.value = scan_string();
			m_current_token.type = Token::Type::StringLiteral;
			break;

		default:
			if (m_current_position >= m_source.size())
			{
				m_current_token.value = "";
				m_current_token.type = Token::Type::Eof;
				break;
			}

			if (std::isdigit(character))
			{
				m_current_token.value = std::to_string(scan_int(character));
				m_current_token.type = Token::Type::IntLiteral;
				break;
			}

			if (std::isalpha(character) || character == '_')
			{
				m_current_token.value = scan_identifier(character);
				m_current_token.type = Token::Type::Identifier;

				Token::Type token_type = get_keyword(m_current_token.value);
				if (m_current_token.type != Token::Type::Eof)
				{
					m_current_token.type = token_type;
				}

				break;
			}

			Utils::fatal_exit("unexpected character '{}' in {} at {}:{}\n", character, m_file_name, m_line, m_line_position);
		}
	}

	Token Lexer::current_token() const
	{
		return m_current_token;
	}

	char Lexer::next_character()
	{
		if (m_current_position >= m_source.size())
		{
			return '\0';
		}
		
		char character = m_source[m_current_position++];

		++m_line_position;

		if (character == '\n')
		{
			++m_line;
			m_line_position = 1;
		}

		return character;
	}

	void Lexer::skip_whitespace()
	{
		char character;
		do
		{
			character = next_character();
		} while (character == ' ' || character == '\t' || character == '\n' || character == '\r' || character == '\f');

		--m_current_position;
	}

	int64_t Lexer::scan_int(char character)
	{
		int64_t number = 0;

		int64_t position = Utils::get_character_position("0123456789", character);
		while (position >= 0)
		{
			number = number * 10 + position;
			character = next_character();

			position = Utils::get_character_position("0123456789", character);
		}

		--m_current_position;

		return number;
	}

	std::string Lexer::scan_string()
	{
		std::string string;

		char character = next_character();
		while (character != '\0')
		{
			if (character == '"')
			{
				return string;
			}

			string += character;
			character = next_character();
		}

		Utils::fatal_exit("string is not terminated\n");
		return "";
	}

	std::string Lexer::scan_identifier(char character)
	{
		std::string string;

		while (isalpha(character) || isdigit(character) || character == '_')
		{
			string += character;
			character = next_character();
		}

		--m_current_position;

		return string;
	}

	Token::Type Lexer::get_keyword(const std::string& keyword)
	{
		switch (keyword[0])
		{
		case 'b':
			if (keyword == "bool")
			{
				return Token::Type::Bool;
			}

			if (keyword == "break")
			{
				return Token::Type::Break;
			}

			if (keyword == "breakall")
			{
				return Token::Type::Breakall;
			}
			break;
		case 'c':
			if (keyword == "char")
			{
				return Token::Type::Char;
			}

			if (keyword == "continue")
			{
				return Token::Type::Continue;
			}
			break;
		case 'd':
			if (keyword == "do")
			{
				return Token::Type::Do;
			}

			if (keyword == "double")
			{
				return Token::Type::Double;
			}
			break;
		case 'e':
			if (keyword == "else")
			{
				return Token::Type::Else;
			}

			if (keyword == "enum")
			{
				return Token::Type::Enum;
			}

			if (keyword == "export")
			{
				return Token::Type::Export;
			}
			break;
		case 'f':
			if (keyword == "float")
			{
				return Token::Type::Float;
			}

			if (keyword == "for")
			{
				return Token::Type::For;
			}

			if (keyword == "function")
			{
				return Token::Type::Function;
			}
			break;
		case 'i':
			if (keyword == "if")
			{
				return Token::Type::If;
			}

			if (keyword == "import")
			{
				return Token::Type::Import;
			}

			if (keyword == "int")
			{
				return Token::Type::Int;
			}

			if (keyword == "int8")
			{
				return Token::Type::Int8;
			}

			if (keyword == "int16")
			{
				return Token::Type::Int16;
			}

			if (keyword == "int32")
			{
				return Token::Type::Int32;
			}

			if (keyword == "int64")
			{
				return Token::Type::Int64;
			}
			break;
		case 'm':
			if (keyword == "mutable")
			{
				return Token::Type::Mutable;
			}
			break;
		case 'o':
			if (keyword == "of")
			{
				return Token::Type::Of;
			}

			if (keyword == "override")
			{
				return Token::Type::Override;
			}
			break;
		case 'p':
			if (keyword == "package")
			{
				return Token::Type::Package;
			}

			if (keyword == "print")
			{
				return Token::Type::Print;
			}
			break;
		case 'r':
			if (keyword == "return")
			{
				return Token::Type::Return;
			}
			break;
		case 's':
			if (keyword == "string")
			{
				return Token::Type::String;
			}

			if (keyword == "struct")
			{
				return Token::Type::Struct;
			}
			break;
		case 'u':
			if (keyword == "uint")
			{
				return Token::Type::Uint;
			}

			if (keyword == "uint8")
			{
				return Token::Type::Uint8;
			}

			if (keyword == "uint16")
			{
				return Token::Type::Uint16;
			}

			if (keyword == "uint32")
			{
				return Token::Type::Uint32;
			}

			if (keyword == "uint64")
			{
				return Token::Type::Uint64;
			}

			if (keyword == "union")
			{
				return Token::Type::Union;
			}
			break;
		case 'v':
			if (keyword == "virtual")
			{
				return Token::Type::Virtual;
			}

			if (keyword == "void")
			{
				return Token::Type::Void;
			}
			break;
		case 'w':
			if (keyword == "while")
			{
				return Token::Type::While;
			}
			break;
		default:
			break;
		}

		return Token::Type::Eof;
	}
} // namespace HyperCompiler
