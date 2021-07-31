/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "HyperCompiler/Lexer.hpp"

#include "HyperCompiler/Logger.hpp"
#include "HyperCompiler/Utils/Utilities.hpp"

#include <cctype>
#include <cstring>
#include <filesystem>

#define DEFINE_MULTIPLE_TOKENS(token_value) \
	case token_value:                       \
		token.set_value(token_value);       \
		character = next_character()

#define DEFINE_MULTIPLE_TOKEN_CASE(token_case, token_type) \
	if (character == (token_case))                         \
	{                                                      \
		token.set_type(token_type);                        \
		token.set_value(token_case);                       \
		break;                                             \
	}

#define DEFINE_MULTIPLE_TOKENS_END(token_type) \
	token.set_type(token_type);                \
	--s_current_position;                      \
	break

#define DEFINE_KEYWORD(identifier, token_type)    \
	do                                            \
	{                                             \
		if (!strcmp(keyword.c_str(), identifier)) \
		{                                         \
			return token_type;                    \
		}                                         \
	} while (0)

namespace HyperCompiler
{
	void Lexer::initialize(const std::string& file_name, const std::string& source)
	{
		s_file_name = file_name;
		s_source = source;
		s_line = 1;
		s_line_position = 0;
		s_current_position = 0;
	}

	Token Lexer::next_token()
	{
		skip_whitespace();

		Token token{};

		char character = next_character();
		switch (character)
		{
		case '\0':
			token.value = "";
			token.type = Token::Type::Eof;
			break;
		case ',':
			token.value = ",";
			token.type = Token::Type::Comma;
			break;
		case '.':
			token.value = ".";
			token.type = Token::Type::Dot;
			break;
		case ':':
			token.value = ":";
			token.type = Token::Type::Colon;
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

			--s_current_position;

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
				token.value = ">";
				token.type = Token::Type::RightArrow;
				break;
			}

			--s_current_position;

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

			--s_current_position;

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

			--s_current_position;

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

			--s_current_position;

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

			--s_current_position;

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

			--s_current_position;

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

			--s_current_position;

			token.value = "^";
			token.type = Token::Type::BitwiseXor;
			break;

		case '~':
			token.value = "~";
			token.type = Token::Type::BitwiseNot;
			break;

		case '=':
			character = next_character();
			if (character == '=')
			{
				token.value = "==";
				token.type = Token::Type::Equal;
				break;
			}

			--s_current_position;

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
			
			--s_current_position;

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

			--s_current_position;

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

			--s_current_position;

			token.value = ">";
			token.type = Token::Type::GreaterThan;
			break;

		case '"':
			token.value = scan_string();
			token.type = Token::Type::StringLiteral;
			return token;

		default:
			if (std::isdigit(character))
			{
				token.value = std::to_string(scan_int(character));
				token.type = Token::Type::IntLiteral;
				break;
			}

			if (std::isalpha(character) || character == '_')
			{
				token.value = scan_identifier(character);
				token.type = Token::Type::Identifier;

				Token::Type token_type = get_keyword(token.value);
				if (token_type != Token::Type::Eof)
				{
					token.type = token_type;
				}

				break;
			}

			Utils::fatal_exit("unexpected character '{}' in {} at {}:{}\n", character, s_file_name, s_line, s_line_position);
		}

		return token;
	}

	char Lexer::next_character()
	{
		char character = s_source[s_current_position];

		++s_current_position;
		++s_line_position;

		if (character == '\n')
		{
			++s_line;
			s_line_position = 1;
		}

		return character;
	}

	void Lexer::skip_whitespace()
	{
		char character;
		do
		{
			character = Lexer::next_character();
		} while (character == ' ' || character == '\t' || character == '\n' || character == '\r' || character == '\f');

		--s_current_position;
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

		--s_current_position;

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

		--s_current_position;

		return string;
	}

	Token::Type Lexer::get_keyword(const std::string& keyword)
	{
		switch (keyword[0])
		{
		case 'b':
			DEFINE_KEYWORD("bool", Token::Type::Bool);
			DEFINE_KEYWORD("break", Token::Type::Break);
			DEFINE_KEYWORD("breakall", Token::Type::Breakall);
			break;
		case 'c':
			DEFINE_KEYWORD("char", Token::Type::Char);
			DEFINE_KEYWORD("continue", Token::Type::Continue);
			break;
		case 'd':
			DEFINE_KEYWORD("do", Token::Type::Do);
			DEFINE_KEYWORD("double", Token::Type::Double);
			break;
		case 'e':
			DEFINE_KEYWORD("else", Token::Type::Else);
			DEFINE_KEYWORD("enum", Token::Type::Enum);
			DEFINE_KEYWORD("export", Token::Type::Export);
			break;
		case 'f':
			DEFINE_KEYWORD("float", Token::Type::Float);
			DEFINE_KEYWORD("for", Token::Type::For);
			DEFINE_KEYWORD("function", Token::Type::Function);
			break;
		case 'i':
			DEFINE_KEYWORD("if", Token::Type::If);
			DEFINE_KEYWORD("import", Token::Type::Import);
			DEFINE_KEYWORD("int", Token::Type::Int);
			DEFINE_KEYWORD("int8", Token::Type::Int8);
			DEFINE_KEYWORD("int16", Token::Type::Int16);
			DEFINE_KEYWORD("int32", Token::Type::Int32);
			DEFINE_KEYWORD("int64", Token::Type::Int64);
			break;
		case 'm':
			DEFINE_KEYWORD("mutable", Token::Type::Mutable);
			break;
		case 'o':
			DEFINE_KEYWORD("of", Token::Type::Of);
			DEFINE_KEYWORD("override", Token::Type::Override);
			break;
		case 'p':
			DEFINE_KEYWORD("package", Token::Type::Package);
			DEFINE_KEYWORD("print", Token::Type::Print);
			break;
		case 'r':
			DEFINE_KEYWORD("return", Token::Type::Return);
			break;
		case 's':
			DEFINE_KEYWORD("string", Token::Type::String);
			DEFINE_KEYWORD("struct", Token::Type::Struct);
			break;
		case 'u':
			DEFINE_KEYWORD("uint", Token::Type::Uint);
			DEFINE_KEYWORD("uint8", Token::Type::Uint8);
			DEFINE_KEYWORD("uint16", Token::Type::Uint16);
			DEFINE_KEYWORD("uint32", Token::Type::Uint32);
			DEFINE_KEYWORD("uint64", Token::Type::Uint64);
			DEFINE_KEYWORD("union", Token::Type::Union);
			break;
		case 'v':
			DEFINE_KEYWORD("virtual", Token::Type::Virtual);
			DEFINE_KEYWORD("void", Token::Type::Void);
			break;
		case 'w':
			DEFINE_KEYWORD("while", Token::Type::While);
			break;
		default:
			break;
		}

		return Token::Type::Eof;
	}
} // namespace HyperCompiler
