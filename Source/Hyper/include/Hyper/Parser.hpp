/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Token.hpp"

#include <memory>
#include <string>

namespace Hyper
{
	class AstNode;
	class Declaration;
	class Expression;
	class Literal;
	class Lexer;
	class Statement;

	class Parser
	{
	public:
		Parser(std::string file, Lexer &lexer);

		std::unique_ptr<AstNode> parse_tree();

	private:
		std::unique_ptr<Declaration> parse_function_declaration();
		std::unique_ptr<Declaration> parse_translation_unit_declaration();
		std::unique_ptr<Declaration> parse_variable_declaration();

		std::unique_ptr<Expression> parse_prefix_expression();
		std::unique_ptr<Expression> parse_postfix_expression();
		std::unique_ptr<Expression> parse_paren_expression();
		std::unique_ptr<Expression> parse_primary_expression();
		std::unique_ptr<Expression> parse_binary_expression(uint8_t precedence);
		std::unique_ptr<Expression> parse_call_expression();
		std::unique_ptr<Expression> parse_identifier_expression();

		std::unique_ptr<Literal> parse_bool_literal();
		std::unique_ptr<Literal> parse_integer_literal();
		std::unique_ptr<Literal> parse_string_literal();

		std::unique_ptr<Statement> parse_statement();
		std::unique_ptr<Statement> parse_assign_statement();
		std::unique_ptr<Statement> parse_compound_statement();
		std::unique_ptr<Statement> parse_compound_assign_statement();
		std::unique_ptr<Statement> parse_expression_statement(
			std::unique_ptr<Expression> expression);
		std::unique_ptr<Statement> parse_if_statement();
		std::unique_ptr<Statement> parse_return_statement();
		std::unique_ptr<Statement> parse_while_statement();

		Token consume() noexcept;
		Token consume(Token::Type token_type) noexcept;
		bool match(Token::Type token_type) const noexcept;

		void save_token(Token token);
		Token current_token() const noexcept;

		std::string consume_type();

		uint8_t map_precedence(Token::Type token_type) const noexcept;

	private:
		std::string m_file;
		Lexer &m_lexer;

		Token m_current_token = {};
		Token m_saved_token = {};
	};
} // namespace Hyper
