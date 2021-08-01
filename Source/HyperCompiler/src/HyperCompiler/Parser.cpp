/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "HyperCompiler/Parser.hpp"

namespace HyperCompiler
{
	void Parser::initialize(Lexer* lexer)
	{
		m_lexer = lexer;
	}

	AstNode* Parser::parse()
	{
		AstNode* ast_node = parse_binary_expression();
		return ast_node;
	}

	Expression* Parser::parse_binary_expression(unsigned int precedence)
	{
		Expression* left = parse_primary_expression();

		Token::Type token_type = m_lexer->current_token().type;
		if (token_type == Token::Type::Eof)
		{
			return left;
		}

		while (get_operator_precedence(token_type) > precedence)
		{
			m_lexer->next_token();
			
			Expression* right = parse_binary_expression(get_operator_precedence(token_type));

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
					return BinaryExpression::Operation::Addition;
				}
			}();

			left = new BinaryExpression(operation, left, right);
			
			token_type = m_lexer->current_token().type;
			if (token_type == Token::Type::Eof)
			{
				return left;
			}
		}

		return left;
	}

	Expression* Parser::parse_primary_expression()
	{
		Expression* expression = nullptr;

		const Token token = m_lexer->current_token();
		switch (token.type)
		{
		case Token::Type::IntLiteral:
			expression = parse_numeric_literal();
			break;
		default:
			break;
		}
		
		return expression;
	}

	Expression* Parser::parse_numeric_literal()
	{
		const Token current_token = m_lexer->current_token();
		if (current_token.type != Token::Type::IntLiteral)
		{
			return nullptr;
		}

		m_lexer->next_token();
		
		NumericLiteral* numeric_literal = new NumericLiteral(static_cast<int64_t>(std::stoll(current_token.value)));
		return reinterpret_cast<Expression*>(numeric_literal);
	}

	unsigned int Parser::get_operator_precedence(Token::Type token_type)
	{
		unsigned int precedence = 0;
		
		switch (token_type)
		{
		case Token::Type::Plus:
		case Token::Type::Minus:
			precedence = 10;
			break;
		case Token::Type::Star:
		case Token::Type::Slash:
			precedence = 20;
			break;
		case Token::Type::Equal:
		case Token::Type::NotEqual:
			precedence = 30;
			break;
		case Token::Type::LessThan:
		case Token::Type::GreaterThan:
		case Token::Type::LessEqual:
		case Token::Type::GreaterEqual:
			precedence = 40;
			break;
		default:
			break;
		}
		
		return precedence;
	}
} // namespace HyperCompiler
