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

	std::unique_ptr<AstNode> Parser::parse()
	{
		return parse_binary_expression(0);
	}

	std::unique_ptr<Expression>
		Parser::parse_binary_expression(uint8_t precedence)
	{
		std::unique_ptr<Expression> left_expression = parse_primary_expression();

		Token::Type token_type = current_token().type;
		if (token_type == Token::Type::Eof)
		{
			return left_expression;
		}

		while (get_operator_precedence(token_type) > precedence)
		{
			advance_token();

			std::unique_ptr<Expression> right_expression =
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
					std::abort();
				}
			}();

			left_expression = std::make_unique<BinaryExpression>(operation, std::move(left_expression), std::move(right_expression));
			
			token_type = current_token().type;
			if (token_type == Token::Type::Eof)
			{
				return left_expression;
			}
		}

		return left_expression;
	}

	std::unique_ptr<Expression> Parser::parse_primary_expression()
	{
		const Token::Type token_type = current_token().type;
		std::unique_ptr<Expression> expression = [&token_type, this]()
		{
			switch (token_type)
			{
			case Token::Type::NumericLiteral:
			{
				return parse_numeric_literal();
			}
			default:
				std::abort();
			}
		}();

		return expression;
	}

	std::unique_ptr<Literal> Parser::parse_numeric_literal()
	{
		const Token token = current_token();
		if (token.type != Token::Type::NumericLiteral)
		{
			return nullptr;
		}

		advance_token();

		return std::make_unique<NumericLiteral>(std::stoll(token.value));
	}

	Token Parser::current_token() const noexcept
	{
		return m_tokens[m_current_token];
	}

	void Parser::advance_token() noexcept
	{
		if (m_current_token >= m_tokens.size())
		{
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
