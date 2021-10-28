/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Token.hpp"

#include <vector>

namespace Hyper
{
	class AstNode;
	class Expression;
	class Literal;

	class Parser
	{
	public:
		explicit Parser(std::vector<Token> tokens);

		AstNode *parse_tree();

	private:
		Expression *parse_binary_expression(uint8_t precedence);
		Expression *parse_primary_expression();

		Literal *parse_numeric_literal();

		Token current_token() const noexcept;
		void advance_token() noexcept;

		uint8_t get_operator_precedence(Token::Type token_type) const noexcept;

	private:
		std::vector<Token> m_tokens = {};
		size_t m_current_token = 0;
	};
} // namespace Hyper
