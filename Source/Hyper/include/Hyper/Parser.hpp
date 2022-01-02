/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Forward.hpp"
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
		Parser(std::string file, Lexer &lexer, Diagnostics &diagnostics);

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
		ExpressionPtr parse_conditional_expression();
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

		Token current_token() const noexcept;
		void save_token(Token token);

		Token consume() noexcept;
		Token consume(Token::Type token_type) noexcept;
		bool match(Token::Type token_type) const noexcept;

		Type consume_type();
		uint8_t map_precedence(Token::Type token_type) const noexcept;
		std::string map_value(Token::Type token_type) const noexcept;

	private:
		std::string m_file;
		Lexer &m_lexer;
		Diagnostics &m_diagnostics;

		Token m_last_token = {};
		Token m_current_token = {};
		Token m_saved_token = {};
	};
} // namespace Hyper
