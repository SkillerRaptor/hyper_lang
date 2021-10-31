/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Parser.hpp"

#include "Hyper/Ast/Declarations/FunctionDeclaration.hpp"
#include "Hyper/Ast/Declarations/VariableDeclaration.hpp"
#include "Hyper/Ast/Expressions/BinaryExpression.hpp"
#include "Hyper/Ast/Expressions/CallExpression.hpp"
#include "Hyper/Ast/Expressions/IdentifierExpression.hpp"
#include "Hyper/Ast/Literals/NumericLiteral.hpp"
#include "Hyper/Ast/Statements/AssignStatement.hpp"
#include "Hyper/Ast/Statements/CompoundStatement.hpp"
#include "Hyper/Ast/Statements/ForStatement.hpp"
#include "Hyper/Ast/Statements/IfStatement.hpp"
#include "Hyper/Ast/Statements/PrintStatement.hpp"
#include "Hyper/Ast/Statements/ReturnStatement.hpp"
#include "Hyper/Ast/Statements/WhileStatement.hpp"

namespace Hyper
{
	Parser::Parser(std::vector<Token> tokens)
		: m_tokens(std::move(tokens))
	{
	}

	std::unique_ptr<AstNode> Parser::parse_tree()
	{
		return parse_program();
	}

	std::unique_ptr<Declaration> Parser::parse_function_declaration()
	{
		match_token(Token::Type::Function);

		const Token identifier = match_token(Token::Type::Identifier);

		match_token(Token::Type::LeftParenthesis);
		match_token(Token::Type::RightParenthesis);
		match_token(Token::Type::RightArrow);

		const Type variable_type = [this]()
		{
			const Token::Type variable_token_type = current_token().type;
			advance_token();
			return match_type(variable_token_type);
		}();

		std::unique_ptr<Statement> body = parse_compound_statement();

		return std::make_unique<FunctionDeclaration>(
			identifier.value, variable_type, std::move(body));
	}

	std::unique_ptr<Declaration> Parser::parse_variable_declaration()
	{
		match_token(Token::Type::Let);

		const Token identifier = match_token(Token::Type::Identifier);

		match_token(Token::Type::Colon);

		bool mut = false;
		if (current_token().type == Token::Type::Mutable)
		{
			advance_token();
			mut = true;
		}

		const Type variable_type = [this]()
		{
			const Token::Type variable_token_type = current_token().type;
			advance_token();
			return match_type(variable_token_type);
		}();

		match_token(Token::Type::Semicolon);

		return std::make_unique<VariableDeclaration>(
			identifier.value, variable_type, mut);
	}

	std::unique_ptr<Expression> Parser::parse_binary_expression(
		uint8_t precedence)
	{
		std::unique_ptr<Expression> left_expression = parse_primary_expression();

		Token::Type token_type = current_token().type;
		if (
			token_type == Token::Type::Semicolon ||
			token_type == Token::Type::RightParenthesis)
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
				case Token::Type::Equal:
					return BinaryExpression::Operation::Equal;
				case Token::Type::NotEqual:
					return BinaryExpression::Operation::NotEqual;
				case Token::Type::LessThan:
					return BinaryExpression::Operation::LessThan;
				case Token::Type::GreaterThan:
					return BinaryExpression::Operation::GreaterThan;
				case Token::Type::LessEqual:
					return BinaryExpression::Operation::LessEqual;
				case Token::Type::GreaterEqual:
					return BinaryExpression::Operation::GreaterEqual;
				default:
					// TODO(SkillerRaptor): Error handling
					std::abort();
				}
			}();

			left_expression = std::make_unique<BinaryExpression>(
				operation, std::move(left_expression), std::move(right_expression));

			token_type = current_token().type;
			if (
				token_type == Token::Type::Semicolon ||
				token_type == Token::Type::RightParenthesis)
			{
				return left_expression;
			}
		}

		return left_expression;
	}

	std::unique_ptr<Expression> Parser::parse_call_expression()
	{
		const Token identifier = match_token(Token::Type::Identifier);
		match_token(Token::Type::LeftParenthesis);
		std::unique_ptr<Expression> expression = parse_binary_expression(0);
		match_token(Token::Type::RightParenthesis);

		return std::make_unique<CallExpression>(
			identifier.value, std::move(expression));
	}

	std::unique_ptr<Expression> Parser::parse_identifier_expression()
	{
		const Token identifier = match_token(Token::Type::Identifier);
		return std::make_unique<IdentifierExpression>(identifier.value);
	}

	std::unique_ptr<Expression> Parser::parse_primary_expression()
	{
		std::unique_ptr<Expression> expression =
			[this]() -> std::unique_ptr<Expression>
		{
			switch (current_token().type)
			{
			case Token::Type::Identifier:
			{
				if (current_token().type == Token::Type::LeftParenthesis)
				{
					return parse_call_expression();
				}

				return parse_identifier_expression();
			}
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
		const Token numeric = match_token(Token::Type::NumericLiteral);
		return std::make_unique<NumericLiteral>(std::stoll(numeric.value));
	}

	std::unique_ptr<Statement> Parser::parse_assign_statement()
	{
		const Token identifier = match_token(Token::Type::Identifier);

		match_token(Token::Type::Assign);

		std::unique_ptr<Expression> expression = parse_binary_expression(0);

		return std::make_unique<AssignStatement>(
			identifier.value, std::move(expression));
	}

	std::unique_ptr<Statement> Parser::parse_compound_statement()
	{
		match_token(Token::Type::LeftBrace);

		std::unique_ptr<Statement> left = nullptr;
		while (true)
		{
			std::unique_ptr<Statement> tree = parse_single_statement();
			if (tree != nullptr)
			{
				if (
					tree->node_category() == AstNode::Category::AssignStatement ||
					tree->node_category() == AstNode::Category::PrintStatement ||
					tree->node_category() == AstNode::Category::ReturnStatement)
				{
					match_token(Token::Type::Semicolon);
				}

				if (left == nullptr)
				{
					left = std::move(tree);
				}
				else
				{
					left = std::make_unique<CompoundStatement>(
						std::move(left), std::move(tree));
				}
			}

			if (current_token().type == Token::Type::RightBrace)
			{
				match_token(Token::Type::RightBrace);
				return left;
			}
		}
	}

	std::unique_ptr<Statement> Parser::parse_for_statement()
	{
		match_token(Token::Type::For);

		std::unique_ptr<Statement> pre_operation = parse_single_statement();
		match_token(Token::Type::Semicolon);

		std::unique_ptr<Expression> condition = parse_binary_expression(0);
		match_token(Token::Type::Semicolon);

		std::unique_ptr<Statement> post_operation = parse_single_statement();
		std::unique_ptr<Statement> body = parse_compound_statement();

		return std::make_unique<ForStatement>(
			std::move(pre_operation),
			std::move(condition),
			std::move(post_operation),
			std::move(body));
	}

	std::unique_ptr<Statement> Parser::parse_if_statement()
	{
		match_token(Token::Type::If);

		std::unique_ptr<Expression> condition = parse_binary_expression(0);
		std::unique_ptr<Statement> true_branch = parse_compound_statement();

		std::unique_ptr<Statement> false_branch = nullptr;
		if (current_token().type == Token::Type::Else)
		{
			advance_token();

			false_branch = parse_compound_statement();
		}

		return std::make_unique<IfStatement>(
			std::move(condition), std::move(true_branch), std::move(false_branch));
	}

	std::unique_ptr<Statement> Parser::parse_print_statement()
	{
		match_token(Token::Type::Print);

		std::unique_ptr<Expression> expression = parse_binary_expression(0);

		return std::make_unique<PrintStatement>(std::move(expression));
	}

	std::unique_ptr<Statement> Parser::parse_program()
	{
		std::unique_ptr<Statement> left = nullptr;
		while (true)
		{
			std::unique_ptr<Statement> tree = parse_function_declaration();
			if (tree != nullptr)
			{
				if (left == nullptr)
				{
					left = std::move(tree);
				}
				else
				{
					left = std::make_unique<CompoundStatement>(
						std::move(left), std::move(tree));
				}
			}

			if (current_token().type == Token::Type::Eof)
			{
				match_token(Token::Type::Eof);
				return left;
			}
		}
	}

	std::unique_ptr<Statement> Parser::parse_return_statement()
	{
		match_token(Token::Type::Return);

		std::unique_ptr<Expression> expression = parse_binary_expression(0);

		return std::make_unique<ReturnStatement>(std::move(expression));
	}

	std::unique_ptr<Statement> Parser::parse_single_statement()
	{
		switch (current_token().type)
		{
		case Token::Type::Identifier:
			if (current_token().type == Token::Type::LeftParenthesis)
			{
				//return parse_call_expression();
			}
			
			return parse_assign_statement();
		case Token::Type::For:
			return parse_for_statement();
		case Token::Type::If:
			return parse_if_statement();
		case Token::Type::Let:
			return parse_variable_declaration();
		case Token::Type::Print:
			return parse_print_statement();
		case Token::Type::Return:
			return parse_return_statement();
		case Token::Type::While:
			return parse_while_statement();
		default:
			// TODO(SkillerRaptor): Error handling
			std::abort();
		}
	}

	std::unique_ptr<Statement> Parser::parse_while_statement()
	{
		match_token(Token::Type::While);

		std::unique_ptr<Expression> condition = parse_binary_expression(0);
		std::unique_ptr<Statement> body = parse_compound_statement();

		return std::make_unique<WhileStatement>(
			std::move(condition), std::move(body));
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
			std::abort();
		}

		++m_current_token;
	}

	Token Parser::peek_token() const noexcept
	{
		return m_tokens[m_current_token + 1];
	}

	Token Parser::match_token(Token::Type token_type) noexcept
	{
		Token token = current_token();
		if (current_token().type != token_type)
		{
			// TODO(SkillerRaptor): Handling error
			std::abort();
		}

		advance_token();

		return token;
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
		case Token::Type::Equal:
		case Token::Type::NotEqual:
			return 30;
		case Token::Type::LessThan:
		case Token::Type::GreaterThan:
		case Token::Type::LessEqual:
		case Token::Type::GreaterEqual:
			return 40;
		default:
			break;
		}

		return 0;
	}

	Type Parser::match_type(Token::Type token_type) const noexcept
	{
		switch (token_type)
		{
		case Token::Type::Int8:
			return Type::Int8;
		case Token::Type::Int16:
			return Type::Int16;
		case Token::Type::Int32:
			return Type::Int32;
		case Token::Type::Int64:
			return Type::Int64;
		case Token::Type::Uint8:
			return Type::Uint8;
		case Token::Type::Uint16:
			return Type::Uint16;
		case Token::Type::Uint32:
			return Type::Uint32;
		case Token::Type::Uint64:
			return Type::Uint64;
		case Token::Type::Void:
			return Type::Void;
		default:
			break;
		}

		// TODO(SkillerRaptor): Error handling
		std::abort();
	}
} // namespace Hyper
