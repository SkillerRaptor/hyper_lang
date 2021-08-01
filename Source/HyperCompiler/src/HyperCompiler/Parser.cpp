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

	Expression* Parser::parse_binary_expression()
	{
		Expression* left = parse_primary_expression();

		const Token token = m_lexer->next_token();
		if (token.type == Token::Type::Eof)
		{
			return left;
		}

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
				return BinaryExpression::Operation::Addition;
			}
		}();

		Expression* right = parse_binary_expression();
		
		BinaryExpression* binary_expression = new BinaryExpression(operation, left, right);
		return reinterpret_cast<Expression*>(binary_expression);
	}

	Expression* Parser::parse_primary_expression()
	{
		Expression* expression = nullptr;

		const Token token = m_lexer->next_token();
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
		
		NumericLiteral* numeric_literal = new NumericLiteral(static_cast<int64_t>(std::stoll(current_token.value)));
		return reinterpret_cast<Expression*>(numeric_literal);
	}
} // namespace HyperCompiler
