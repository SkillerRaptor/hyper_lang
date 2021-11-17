/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Forward.hpp"
#include "Hyper/DataType.hpp"
#include "Hyper/Token.hpp"

#include <memory>

namespace Hyper
{
	class Scanner;

	class Parser
	{
	public:
		Parser(std::string file, Scanner &scanner);

		AstPtr parse_tree();

	private:
		DeclarationPtr parse_function_declaration();
		DeclarationPtr parse_translation_unit_declaration();
		DeclarationPtr parse_variable_declaration();

		ExpressionPtr parse_primary_expression();
		ExpressionPtr parse_binary_expression(uint8_t min_precedence);
		ExpressionPtr parse_call_expression();
		ExpressionPtr parse_identifier_expression();

		LiteralPtr parse_numeric_literal();
		LiteralPtr parse_string_literal();

		StatementPtr parse_statement();
		StatementPtr parse_assign_statement();
		StatementPtr parse_compound_statement();
		StatementPtr parse_expression_statement(ExpressionPtr expression);
		StatementPtr parse_for_statement();
		StatementPtr parse_if_statement();
		StatementPtr parse_print_statement();
		StatementPtr parse_return_statement();
		StatementPtr parse_while_statement();

		bool match(Token::Type token_type) const;

		Token consume();
		Token consume(Token::Type token_type);

		DataType map_type(Token::Type token_type) const;
		uint8_t map_precedence(Token::Type token_type) const;

		void save_token(Token token);
		void expected(std::string_view expected) const;

	private:
		std::string m_file;
		Scanner &m_scanner;

		Token m_current_token = {};
		Token m_saved_token = {};
	};
} // namespace Hyper
