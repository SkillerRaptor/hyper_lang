/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Parser.hpp"

#include "Hyper/Ast/Expressions/BinaryExpression.hpp"
#include "Hyper/Ast/Literals/NumericLiteral.hpp"

namespace Hyper
{
	Parser::Parser(std::vector<Token> tokens)
		: m_tokens(std::move(tokens))
	{
	}

	AstNode *Parser::parse_tree()
	{
		return parse_binary_expression(0);
	}

	Expression *Parser::parse_binary_expression(uint8_t precedence)
	{
		Expression *left_expression = parse_primary_expression();

		Token::Type token_type = current_token().type;
		if (token_type == Token::Type::Eof)
		{
			return left_expression;
		}

		while (get_operator_precedence(token_type) > precedence)
		{
			advance_token();

			Expression *right_expression =
				parse_binary_expression(get_operator_precedence(token_type));

			const BinaryExpression::Operation operation = [&token_type]()
			{
				switch (token_type)
				{
				case Token::Type::Plus:
					return BinaryExpression::Operation::Addition;
				case Token::Type::Minus:
					return BinaryExpression::Operation::Subtraction;
				case Token::Type::Star:
					return BinaryExpression::Operation::Multiplication;
				case Token::Type::Slash:
					return BinaryExpression::Operation::Division;
				default:
					// TODO(SkillerRaptor): Error handling
					std::abort();
				}
			}();

			left_expression =
				new BinaryExpression(operation, left_expression, right_expression);

			token_type = current_token().type;
			if (token_type == Token::Type::Eof)
			{
				return left_expression;
			}
		}

		return left_expression;
	}

	Expression *Parser::parse_primary_expression()
	{
		const Token::Type token_type = current_token().type;
		Expression *expression = [&token_type, this]()
		{
			switch (token_type)
			{
			case Token::Type::NumericLiteral:
			{
				return parse_numeric_literal();
			}
			default:
				// TODO(SkillerRaptor): Error handling
				std::abort();
			}
		}();

		return expression;
	}

	Literal *Parser::parse_numeric_literal()
	{
		const Token token = current_token();
		if (token.type != Token::Type::NumericLiteral)
		{
			// TODO(SkillerRaptor): Error handling
			return nullptr;
		}

		advance_token();

		return new NumericLiteral(std::stoll(token.value));
	}

	Token Parser::current_token() const noexcept
	{
		return m_tokens[m_current_token];
	}

	void Parser::advance_token() noexcept
	{
		if (m_current_token >= m_tokens.size())
		{
			// TODO(SkillerRaptor): Error handling
			return;
		}

		++m_current_token;
	}

	uint8_t Parser::get_operator_precedence(Token::Type token_type) const noexcept
	{
		switch (token_type)
		{
		case Token::Type::Plus:
		case Token::Type::Minus:
			return 10;
		case Token::Type::Star:
		case Token::Type::Slash:
			return 20;
		default:
			break;
		}

		return 0;
	}
} // namespace Hyper
