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
		return parse_binary_expression();
	}

	std::unique_ptr<Expression> Parser::parse_binary_expression()
	{
		std::unique_ptr<Expression> left_expression = parse_primary_expression();

		const Token token = current_token();
		if (token.type == Token::Type::Eof)
		{
			return left_expression;
		}

		advance_token();

		std::unique_ptr<Expression> right_expression = parse_binary_expression();

		const BinaryExpression::Operation operation = [&token]()
		{
			switch (token.type)
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

		return std::make_unique<BinaryExpression>(
			operation, std::move(left_expression), std::move(right_expression));
	}

	std::unique_ptr<Expression> Parser::parse_primary_expression()
	{
		const Token token = current_token();
		std::unique_ptr<Expression> expression = [&token, this]()
		{
			switch (token.type)
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
} // namespace Hyper
