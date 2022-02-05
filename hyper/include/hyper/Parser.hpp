/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/forward.hpp"
#include "hyper/ast/identifier.hpp"
#include "hyper/data_type.hpp"
#include "hyper/diagnostics.hpp"
#include "hyper/token.hpp"

#include <memory>
#include <string>
#include <vector>

namespace hyper
{
	class Diagnostics;
	class Lexer;

	class Parser
	{
	public:
		Parser(
			const Diagnostics &diagnostics,
			const std::vector<Token> &tokens,
			std::string file);

		AstNodePtr parse();

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
		LiteralPtr parse_floating_literal();
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

		Token last_token() const noexcept;
		Token current_token() const noexcept;
		Token peek_token() const noexcept;

		void rewind_token() noexcept;

		bool match(Token::Type token_type) const noexcept;

		Token consume() noexcept;
		Token consume(Token::Type token_type) noexcept;

		DataType consume_type();
		Identifier consume_identifier();

		uint8_t get_operator_precedence(Token::Type token_type) const noexcept;

	private:
		const Diagnostics &m_diagnostics;
		const std::vector<Token> &m_tokens;
		std::string m_file;

		size_t m_token_index = 0;
	};
} // namespace hyper
