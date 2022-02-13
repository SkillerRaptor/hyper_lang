/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/lexer.hpp"

#include "hyper/diagnostics.hpp"
#include "hyper/utilities.hpp"

namespace hyper
{
	Lexer::Lexer(const Diagnostics &diagnostics, std::string text)
		: m_diagnostics(diagnostics)
		, m_text(std::move(text))
	{
	}

	std::vector<Token> Lexer::lex()
	{
		std::vector<Token> tokens = {};
		while (!has_reached_end())
		{
			const Token token = next_token();
			if (token.type() != Token::Type::Invalid)
			{
				tokens.emplace_back(token);
			}
		}

		const SourceRange source_range = {
			.start = {
				.line = m_line,
				.column = m_column,
			},
			.end = {
				.line = m_line,
				.column = m_column,
			},
		};

		tokens.emplace_back("", Token::Type::Eof, source_range);

		return tokens;
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
				return lex_comment();
			}

			if (peek() == '*')
			{
				return lex_block_comment();
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
			value = lex_string();
			type = Token::Type::StringLiteral;
			break;
		default:
			if (has_reached_end())
			{
				break;
			}

			if (std::isdigit(m_current_char))
			{
				const auto &[literal_value, literal_type] = lex_numeric_literal();
				value = literal_value;
				type = literal_type;
				break;
			}

			if (std::isalpha(m_current_char))
			{
				value = lex_identifier();
				type = Token::Type::Identifier;

				const Token::Type keyword_type = fetch_type(value);
				if (keyword_type != Token::Type::Invalid)
				{
					type = keyword_type;
				}

				break;
			}

			value = m_current_char;
			type = Token::Type::Invalid;
			break;
		}

		const SourceRange source_range = {
		 .start = start,
		 .end = {
			 .line = m_line,
			 .column = m_column,
		 },
	 };

		return Token{ value, type, source_range };
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

	Token Lexer::lex_comment() noexcept
	{
		advance();
		while (peek() != '\n')
		{
			advance();
		}

		return next_token();
	}

	Token Lexer::lex_block_comment() noexcept
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
				 .end = {
					 .line = m_line,
					 .column = m_column - 1,
				 },
			 };

				m_diagnostics.error(source_range, Diagnostics::ErrorCode::E0001);
			}
		}

		return next_token();
	}

	std::string Lexer::lex_string()
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

			if (has_reached_end())
			{
				const SourceRange source_range = {
				 .start = start,
				 .end = {
					 .line = m_line,
					 .column = m_column - 1,
				 },
			 };

				m_diagnostics.error(source_range, Diagnostics::ErrorCode::E0002);
			}
		} while (m_current_char != '"');

		return string;
	}

	std::string Lexer::lex_identifier()
	{
		std::string string(1, m_current_char);
		while (std::isalpha(peek()) || std::isdigit(peek()) || peek() == '_')
		{
			advance();
			string += m_current_char;
		}

		return string;
	}

	std::pair<std::string, Token::Type> Lexer::lex_numeric_literal()
	{
		if (m_current_char != '0')
		{
			return lex_decimal_literal();
		}

		switch (peek())
		{
		case 'b':
			return { lex_binary_literal(), Token::Type::IntegerLiteral };
		case 'o':
			return { lex_oct_literal(), Token::Type::IntegerLiteral };
		case 'x':
			return { lex_hex_literal(), Token::Type::IntegerLiteral };
		default:
			return lex_decimal_literal();
		}
	}

	std::pair<std::string, Token::Type> Lexer::lex_decimal_literal()
	{
		std::string string(1, m_current_char);

		constexpr auto is_decimal = [](char character) noexcept
		{
			return (character >= '0' && character <= '9');
		};

		while (is_decimal(peek()))
		{
			advance();
			string += m_current_char;
		}

		if (peek() == '.')
		{
			advance();
			string += m_current_char;

			while (is_decimal(peek()))
			{
				advance();
				string += m_current_char;
			}

			return { string, Token::Type::FloatingLiteral };
		}

		return { string, Token::Type::IntegerLiteral };
	}

	std::string Lexer::lex_binary_literal()
	{
		std::string string = "0b";
		advance();

		constexpr auto is_binary = [](char character) noexcept
		{
			return (character >= '0' && character <= '1');
		};

		while (is_binary(peek()))
		{
			advance();
			string += m_current_char;
		}

		return string;
	}

	std::string Lexer::lex_oct_literal()
	{
		std::string string = "0o";
		advance();

		constexpr auto is_oct = [](char character) noexcept
		{
			return (character >= '0' && character <= '7');
		};

		while (is_oct(peek()))
		{
			advance();
			string += m_current_char;
		}

		return string;
	}

	std::string Lexer::lex_hex_literal()
	{
		std::string string = "0x";
		advance();

		constexpr auto is_hex = [](char character) noexcept
		{
			return (character >= '0' && character <= '9') ||
						 (character >= 'A' && character <= 'F') ||
						 (character >= 'a' && character <= 'f');
		};

		while (is_hex(peek()))
		{
			advance();
			string += m_current_char;
		}

		return string;
	}

	Token::Type Lexer::fetch_type(std::string_view value) const noexcept
	{
		switch (Utilities::hash(value))
		{
		case Utilities::hash("as"):
			return Token::Type::As;
		case Utilities::hash("break"):
			return Token::Type::Break;
		case Utilities::hash("else"):
			return Token::Type::Else;
		case Utilities::hash("for"):
			return Token::Type::For;
		case Utilities::hash("if"):
			return Token::Type::If;
		case Utilities::hash("return"):
			return Token::Type::Return;
		case Utilities::hash("while"):
			return Token::Type::While;
		case Utilities::hash("export"):
			return Token::Type::Export;
		case Utilities::hash("import"):
			return Token::Type::Import;
		case Utilities::hash("fn"):
			return Token::Type::Function;
		case Utilities::hash("let"):
			return Token::Type::Let;
		case Utilities::hash("mutable"):
			return Token::Type::Mutable;
		case Utilities::hash("struct"):
			return Token::Type::Struct;
		case Utilities::hash("bool"):
			return Token::Type::Bool;
		case Utilities::hash("i8"):
			return Token::Type::Int8;
		case Utilities::hash("i16"):
			return Token::Type::Int16;
		case Utilities::hash("i32"):
			return Token::Type::Int32;
		case Utilities::hash("i64"):
			return Token::Type::Int64;
		case Utilities::hash("u8"):
			return Token::Type::Uint8;
		case Utilities::hash("u16"):
			return Token::Type::Uint16;
		case Utilities::hash("u32"):
			return Token::Type::Uint32;
		case Utilities::hash("u64"):
			return Token::Type::Uint64;
		case Utilities::hash("isize"):
			return Token::Type::ISize;
		case Utilities::hash("usize"):
			return Token::Type::USize;
		case Utilities::hash("f32"):
			return Token::Type::Float32;
		case Utilities::hash("f64"):
			return Token::Type::Float64;
		case Utilities::hash("string"):
			return Token::Type::String;
		case Utilities::hash("void"):
			return Token::Type::Void;
		case Utilities::hash("true"):
		case Utilities::hash("false"):
			return Token::Type::BoolLiteral;
		case Utilities::hash("print"): // NOTE: Remove after debug
			return Token::Type::Print;
		default:
			return Token::Type::Invalid;
		}
	}
} // namespace hyper
