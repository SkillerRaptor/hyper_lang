/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Forward.hpp"
#include "Hyper/Diagnostics.hpp"
#include "Hyper/Token.hpp"
#include "Hyper/Type.hpp"

#include <string>

namespace Hyper
{
	class Diagnostics;
	class Lexer;

	class Parser
	{
	public:
		Parser(Diagnostics &diagnostics, Lexer &lexer, std::string file);

		AstPtr parse_tree();

	private:
		DeclarationPtr parse_function_declaration();
		DeclarationPtr parse_translation_unit_declaration();
		DeclarationPtr parse_variable_declaration();

		ExpressionPtr parse_prefix_expression();
		ExpressionPtr parse_postfix_expression();
		ExpressionPtr parse_paren_expression();
		ExpressionPtr parse_primary_expression();
		ExpressionPtr parse_binary_expression(uint8_t precedence);
		ExpressionPtr parse_call_expression();
		ExpressionPtr parse_identifier_expression();

		LiteralPtr parse_bool_literal();
		LiteralPtr parse_integer_literal();
		LiteralPtr parse_string_literal();

		StatementPtr parse_statement();
		StatementPtr parse_assign_statement();
		StatementPtr parse_compound_statement();
		StatementPtr parse_compound_assign_statement();
		StatementPtr parse_expression_statement(ExpressionPtr expression);
		StatementPtr parse_if_statement();
		StatementPtr parse_return_statement();
		StatementPtr parse_while_statement();

		const Token &current_token() const noexcept;
		void save_token(Token token);

		Token consume() noexcept;
		Type consume_type();

		uint8_t map_precedence(Token::Type token_type) const noexcept;

		template <Token::Type T>
		bool match() const noexcept
		{
			return current_token().type == T;
		}

		template <Token::Type T>
		Token consume() noexcept
		{
			if (!match<T>())
			{
				const Token &token = current_token();

				const Position position = [&]()
				{
					if constexpr (T == Token::Type::Semicolon)
					{
						return m_last_token.range.start;
					}
					else
					{
						return token.range.start;
					}
				}();

				const SourceRange source_range = {
					.start = position,
					.end = token.range.end,
				};

				m_diagnostics.error(
					source_range,
					"expected '{}', found '{}'",
					map_type<T>(),
					token.value);
			}

			return consume();
		}

		template <Token::Type T>
		constexpr std::string_view map_type() const noexcept
		{
			switch (T)
			{
			case Token::Type::Eof:
				return "EOF";
			case Token::Type::Arrow:
				return "->";
			case Token::Type::Dot:
				return ".";
			case Token::Type::Colon:
				return ":";
			case Token::Type::Identifier:
				return "identifier";
			case Token::Type::Semicolon:
				return ";";
			case Token::Type::Assign:
				return "=";
			case Token::Type::PlusEqual:
				return "!=";
			case Token::Type::MinusEqual:
				return "-=";
			case Token::Type::StarEqual:
				return "*=";
			case Token::Type::SlashEqual:
				return "/=";
			case Token::Type::PercentEqual:
				return "%=";
			case Token::Type::BitwiseAndEqual:
				return "&=";
			case Token::Type::BitwiseOrEqual:
				return "|=";
			case Token::Type::BitwiseXorEqual:
				return "^=";
			case Token::Type::LeftShiftEqual:
				return "<<=";
			case Token::Type::RightShiftEqual:
				return ">>=";
			case Token::Type::Increment:
				return "++";
			case Token::Type::Decrement:
				return "--";
			case Token::Type::Plus:
				return "+";
			case Token::Type::Minus:
				return "-";
			case Token::Type::Star:
				return "*";
			case Token::Type::Slash:
				return "/";
			case Token::Type::Percent:
				return "%";
			case Token::Type::BitwiseAnd:
				return "&";
			case Token::Type::BitwiseOr:
				return "|";
			case Token::Type::BitwiseNot:
				return "~";
			case Token::Type::BitwiseXor:
				return "^";
			case Token::Type::LeftShift:
				return "<<";
			case Token::Type::RightShift:
				return ">>";
			case Token::Type::LogicalNot:
				return "!";
			case Token::Type::LogicalAnd:
				return "&&";
			case Token::Type::LogicalOr:
				return "||";
			case Token::Type::Equal:
				return "==";
			case Token::Type::NotEqual:
				return "!=";
			case Token::Type::LessThan:
				return "<";
			case Token::Type::GreaterThan:
				return ">";
			case Token::Type::LessEqual:
				return "<=";
			case Token::Type::GreaterEqual:
				return ">=";
			case Token::Type::QuestionMark:
				return "?";
			case Token::Type::CurlyLeftBracket:
				return "{";
			case Token::Type::CurlyRightBracket:
				return "}";
			case Token::Type::SquareLeftBracket:
				return "[";
			case Token::Type::SquareRightBracket:
				return "]";
			case Token::Type::RoundLeftBracket:
				return "(";
			case Token::Type::RoundRightBracket:
				return ")";
			case Token::Type::Break:
				return "break";
			case Token::Type::Else:
				return "else";
			case Token::Type::For:
				return "for";
			case Token::Type::If:
				return "if";
			case Token::Type::Return:
				return "return";
			case Token::Type::While:
				return "while";
			case Token::Type::Export:
				return "export";
			case Token::Type::Import:
				return "import";
			case Token::Type::Function:
				return "fn";
			case Token::Type::Let:
				return "let";
			case Token::Type::Mutable:
				return "mutable";
			case Token::Type::Struct:
				return "struct";
			case Token::Type::Bool:
				return "bool";
			case Token::Type::Int8:
				return "i8";
			case Token::Type::Int16:
				return "";
			case Token::Type::Int32:
				return "i32";
			case Token::Type::Int64:
				return "i64";
			case Token::Type::Uint8:
				return "u8";
			case Token::Type::Uint16:
				return "u16";
			case Token::Type::Uint32:
				return "u32";
			case Token::Type::Uint64:
				return "u64";
			case Token::Type::ISize:
				return "isize";
			case Token::Type::USize:
				return "usize";
			case Token::Type::Float32:
				return "f32";
			case Token::Type::Float64:
				return "f64";
			case Token::Type::String:
				return "string";
			case Token::Type::Void:
				return "void";
			case Token::Type::BoolLiteral:
				return "bool literal";
			case Token::Type::IntegerLiteral:
				return "integer literal";
			case Token::Type::StringLiteral:
				return "string literal";
			default:
				return "";
			}
		}

	private:
		Diagnostics &m_diagnostics;
		Lexer &m_lexer;
		std::string m_file;

		Token m_last_token = {};
		Token m_current_token = {};
		Token m_saved_token = {};
	};
} // namespace Hyper
