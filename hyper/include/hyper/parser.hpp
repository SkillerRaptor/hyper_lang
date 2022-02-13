/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/data_type.hpp"
#include "hyper/diagnostics.hpp"
#include "hyper/token.hpp"
#include "identifier.hpp"

#include <memory>
#include <string>
#include <vector>

namespace hyper
{
	class AstNode;
	class Declaration;
	class Expression;
	class Literal;
	class Statement;

	class Diagnostics;
	class Lexer;

	class Parser
	{
	public:
		Parser(
			const Diagnostics &diagnostics,
			const std::vector<Token> &tokens,
			std::string file);

		AstNode *parse();

	private:
		Declaration *parse_export_declaration();
		Declaration *parse_function_declaration();
		Declaration *parse_import_declaration();
		Declaration *parse_translation_unit_declaration();
		Declaration *parse_variable_declaration();

		Expression *parse_prefix_expression();
		Expression *parse_postfix_expression();
		Expression *parse_paren_expression();
		Expression *parse_primary_expression();
		Expression *parse_binary_expression(uint8_t precedence);
		Expression *parse_call_expression();
		Expression *parse_identifier_expression();

		Literal *parse_bool_literal();
		Literal *parse_floating_literal();
		Literal *parse_integer_literal();
		Literal *parse_string_literal();

		Statement *parse_statement();
		Statement *parse_assign_statement();
		Statement *parse_compound_statement();
		Statement *parse_compound_assign_statement();
		Statement *parse_expression_statement(Expression *expression);
		Statement *parse_if_statement();
		Statement *parse_print_statement();
		Statement *parse_return_statement();
		Statement *parse_while_statement();

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
