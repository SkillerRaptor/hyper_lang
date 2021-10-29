/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Parser.hpp"

#include "Hyper/Ast/Declarations/VariableDeclaration.hpp"
#include "Hyper/Ast/Expressions/BinaryExpression.hpp"
#include "Hyper/Ast/Literals/NumericLiteral.hpp"
#include "Hyper/Ast/Statements/AssignStatement.hpp"

namespace Hyper
{
	Parser::Parser(std::vector<Token> tokens)
		: m_tokens(std::move(tokens))
	{
	}

	std::unique_ptr<AstNode> Parser::parse_tree()
	{
		return parse_statements();
	}

	std::unique_ptr<Declaration> Parser::parse_variable_declaration()
	{
		const Token::Type let_token_type = current_token().type;
		if (let_token_type != Token::Type::Let)
		{
			// TODO(SkillerRaptor): Error handling
			return nullptr;
		}

		advance_token();

		const Token identifier_token = current_token();
		if (identifier_token.type != Token::Type::Identifier)
		{
			// TODO(SkillerRaptor): Error handling
			return nullptr;
		}

		advance_token();
		
		const Token::Type colon_token_type = current_token().type;
		if (colon_token_type != Token::Type::Colon)
		{
			// TODO(SkillerRaptor): Error handling
			return nullptr;
		}

		advance_token();
		
		const Token::Type mutable_token_type = current_token().type;
		if (mutable_token_type != Token::Type::Mutable)
		{
			// TODO(SkillerRaptor): Error handling
			return nullptr;
		}

		advance_token();
		
		const Token::Type type_token_type = current_token().type;
		if (type_token_type != Token::Type::Int64)
		{
			// TODO(SkillerRaptor): Error handling
			return nullptr;
		}

		advance_token();

		const Token::Type semicolon_token_type = current_token().type;
		if (semicolon_token_type != Token::Type::Semicolon)
		{
			// TODO(SkillerRaptor): Error handling
			return nullptr;
		}

		advance_token();

		return std::make_unique<VariableDeclaration>(
			identifier_token.value, VariableDeclaration::Type::Int64);
	}

	std::unique_ptr<Expression> Parser::parse_binary_expression(
		uint8_t precedence)
	{
		std::unique_ptr<Expression> left_expression = parse_primary_expression();

		Token::Type token_type = current_token().type;
		if (token_type == Token::Type::Semicolon)
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
					// TODO(SkillerRaptor): Error handling
					std::abort();
				}
			}();

			left_expression = std::make_unique<BinaryExpression>(
				operation, std::move(left_expression), std::move(right_expression));

			token_type = current_token().type;
			if (token_type == Token::Type::Semicolon)
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
				// TODO(SkillerRaptor): Error handling
				std::abort();
			}
		}();

		return expression;
	}

	std::unique_ptr<Literal> Parser::parse_numeric_literal()
	{
		const Token numeric_literal_token = current_token();
		if (numeric_literal_token.type != Token::Type::NumericLiteral)
		{
			// TODO(SkillerRaptor): Error handling
			return nullptr;
		}

		advance_token();

		return std::make_unique<NumericLiteral>(
			std::stoll(numeric_literal_token.value));
	}

	std::unique_ptr<Statement> Parser::parse_statements()
	{
		// FIXME(SkillerRaptor): Only the first statement will be parsed

		const Token::Type token_type = current_token().type;
		switch (token_type)
		{
		case Token::Type::Identifier:
			//return parse_assign_statement();
		case Token::Type::Print:
			//return parse_print_statement();
		case Token::Type::Let:
			return parse_variable_declaration();
		default:
			// TODO(SkillerRaptor): Error handling
			std::abort();
		}
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
