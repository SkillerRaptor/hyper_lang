/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Token.hpp"

#include <memory>
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

		std::unique_ptr<AstNode> parse_tree();

	private:
		std::unique_ptr<Expression> parse_binary_expression(uint8_t precedence);
		std::unique_ptr<Expression> parse_primary_expression();

		std::unique_ptr<Literal> parse_numeric_literal();

		Token current_token() const noexcept;
		void advance_token() noexcept;
		void match_token(Token::Type token_type) noexcept;

		uint8_t get_operator_precedence(Token::Type token_type) const noexcept;

	private:
		std::vector<Token> m_tokens = {};
		size_t m_current_token = 0;
	};
} // namespace Hyper
