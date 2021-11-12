/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Parser.hpp"

#include "Hyper/Ast/Declarations/FunctionDeclaration.hpp"
#include "Hyper/Ast/Declarations/TranslationUnitDeclaration.hpp"
#include "Hyper/Ast/Declarations/VariableDeclaration.hpp"
#include "Hyper/Ast/Expressions/BinaryExpression.hpp"
#include "Hyper/Ast/Expressions/CallExpression.hpp"
#include "Hyper/Ast/Expressions/IdentifierExpression.hpp"
#include "Hyper/Ast/Literals/NumericLiteral.hpp"
#include "Hyper/Ast/Literals/StringLiteral.hpp"
#include "Hyper/Ast/Statements/AssignStatement.hpp"
#include "Hyper/Ast/Statements/CompoundStatement.hpp"
#include "Hyper/Ast/Statements/ExpressionStatement.hpp"
#include "Hyper/Ast/Statements/ForStatement.hpp"
#include "Hyper/Ast/Statements/IfStatement.hpp"
#include "Hyper/Ast/Statements/PrintStatement.hpp"
#include "Hyper/Ast/Statements/ReturnStatement.hpp"
#include "Hyper/Ast/Statements/WhileStatement.hpp"
#include "Hyper/Logger.hpp"
#include "Hyper/Scanner.hpp"

#include <utility>

namespace Hyper
{
	Parser::Parser(std::string file, Scanner &scanner)
		: m_file(std::move(file))
		, m_scanner(scanner)
	{
		consume();
	}

	std::unique_ptr<AstNode> Parser::parse_tree()
	{
		return parse_translation_unit_declaration();
	}

	DeclarationPtr Parser::parse_function_declaration()
	{
		consume(Token::Type::Function);

		const std::string function_name = consume(Token::Type::Identifier).value;

		consume(Token::Type::LeftRoundBracket);
		// TODO(SkillerRaptor): Implement arguments
		std::vector<DeclarationPtr> arguments = {};
		consume(Token::Type::RightRoundBracket);
		consume(Token::Type::RightArrow);

		const Type return_type = map_type(m_current_token.type);
		consume();

		StatementPtr body = parse_compound_statement();

		return std::make_unique<FunctionDeclaration>(
			function_name, std::move(arguments), return_type, std::move(body));
	}

	DeclarationPtr Parser::parse_translation_unit_declaration()
	{
		std::vector<StatementPtr> statements = {};

		while (!match(Token::Type::Eof))
		{
			StatementPtr statement = parse_statement();
			statements.push_back(std::move(statement));
		}

		return std::make_unique<TranslationUnitDeclaration>(
			m_file, std::move(statements));
	}

	DeclarationPtr Parser::parse_variable_declaration()
	{
		consume(Token::Type::Let);

		const std::string name = consume(Token::Type::Identifier).value;

		consume(Token::Type::Colon);

		VariableDeclaration::Immutable immutable =
			VariableDeclaration::Immutable::Yes;
		if (match(Token::Type::Mutable))
		{
			consume();
			immutable = VariableDeclaration::Immutable::No;
		}

		const Type type = map_type(m_current_token.type);
		consume();

		consume(Token::Type::Semicolon);

		// TODO(SkillerRaptor): Implementing assignment

		return std::make_unique<VariableDeclaration>(name, type, immutable);
	}

	ExpressionPtr Parser::parse_primary_expression()
	{
		switch (m_current_token.type)
		{
		case Token::Type::Identifier:
			return parse_identifier_expression();
		case Token::Type::Minus:
		case Token::Type::NumericLiteral:
			return parse_numeric_literal();
		case Token::Type::StringLiteral:
			return parse_string_literal();
		default:
			expected("Expression");
			break;
		}

		return nullptr;
	}

	ExpressionPtr Parser::parse_binary_expression(uint8_t min_precedence)
	{
		ExpressionPtr left = parse_primary_expression();

		Token::Type token_type = m_current_token.type;
		if (
			token_type == Token::Type::Semicolon ||
			token_type == Token::Type::RightRoundBracket)
		{
			return left;
		}

		while (map_precedence(token_type) > min_precedence)
		{
			consume();

			ExpressionPtr right = parse_binary_expression(map_precedence(token_type));

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

			left = std::make_unique<BinaryExpression>(
				operation, std::move(left), std::move(right));

			token_type = m_current_token.type;
			if (
				token_type == Token::Type::Semicolon ||
				token_type == Token::Type::RightRoundBracket)
			{
				return left;
			}
		}

		return left;
	}

	ExpressionPtr Parser::parse_call_expression()
	{
		std::string function = consume(Token::Type::Identifier).value;

		consume(Token::Type::LeftRoundBracket);
		std::vector<ExpressionPtr> arguments = {};
		// TODO(SkillerRaptor): Implementing arguments
		consume(Token::Type::RightRoundBracket);

		return std::make_unique<CallExpression>(function, std::move(arguments));
	}

	ExpressionPtr Parser::parse_identifier_expression()
	{
		const Token identifier_token = consume(Token::Type::Identifier);

		if (match(Token::Type::LeftRoundBracket))
		{
			save_token(identifier_token);
			return parse_call_expression();
		}

		return std::make_unique<IdentifierExpression>(identifier_token.value);
	}

	LiteralPtr Parser::parse_numeric_literal()
	{
		NumericLiteral::Type type = NumericLiteral::Type::Unsigned;
		if (match(Token::Type::Minus))
		{
			consume();
			type = NumericLiteral::Type::Signed;
		}

		uint64_t value = std::stoull(consume(Token::Type::NumericLiteral).value);
		if (type == NumericLiteral::Type::Signed)
		{
			value += static_cast<uint64_t>(std::numeric_limits<int64_t>::min());
		}

		return std::make_unique<NumericLiteral>(type, value);
	}

	LiteralPtr Parser::parse_string_literal()
	{
		std::string value = consume(Token::Type::StringLiteral).value;
		return std::make_unique<StringLiteral>(value);
	}

	StatementPtr Parser::parse_statement()
	{
		switch (m_current_token.type)
		{
		case Token::Type::Identifier:
			return parse_assign_statement();
		case Token::Type::For:
			return parse_for_statement();
		case Token::Type::Function:
			return parse_function_declaration();
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
			expected("Statement");
			break;
		}

		return nullptr;
	}

	StatementPtr Parser::parse_assign_statement()
	{
		const Token identifier_token = consume(Token::Type::Identifier);

		if (match(Token::Type::LeftRoundBracket))
		{
			save_token(identifier_token);
			return parse_expression_statement(parse_call_expression());
		}

		consume(Token::Type::Assign);

		ExpressionPtr expression = parse_binary_expression(0);

		return std::make_unique<AssignStatement>(identifier_token.value, std::move(expression));
	}

	StatementPtr Parser::parse_compound_statement()
	{
		consume(Token::Type::LeftCurlyBracket);

		std::vector<StatementPtr> statements = {};
		while (true)
		{
			StatementPtr tree = parse_statement();
			if (tree != nullptr)
			{
				if (
					tree->class_category() == AstNode::Category::AssignStatement ||
					tree->class_category() == AstNode::Category::ExpressionStatement ||
					tree->class_category() == AstNode::Category::PrintStatement ||
					tree->class_category() == AstNode::Category::ReturnStatement)
				{
					consume(Token::Type::Semicolon);
				}

				statements.push_back(std::move(tree));
			}

			if (match(Token::Type::RightCurlyBracket))
			{
				break;
			}
		}

		consume(Token::Type::RightCurlyBracket);

		return std::make_unique<CompoundStatement>(std::move(statements));
	}

	StatementPtr Parser::parse_expression_statement(ExpressionPtr expression)
	{
		return std::make_unique<ExpressionStatement>(std::move(expression));
	}

	StatementPtr Parser::parse_for_statement()
	{
		consume(Token::Type::For);

		consume(Token::Type::LeftRoundBracket);
		std::unique_ptr<Statement> pre_operation = parse_statement();
		consume(Token::Type::Semicolon);

		std::unique_ptr<Expression> condition = parse_binary_expression(0);
		consume(Token::Type::Semicolon);

		std::unique_ptr<Statement> post_operation = parse_statement();
		consume(Token::Type::RightRoundBracket);

		std::unique_ptr<Statement> body = parse_compound_statement();

		return std::make_unique<ForStatement>(
			std::move(pre_operation),
			std::move(condition),
			std::move(post_operation),
			std::move(body));
	}

	StatementPtr Parser::parse_if_statement()
	{
		consume(Token::Type::If);

		consume(Token::Type::LeftRoundBracket);
		ExpressionPtr condition = parse_binary_expression(0);
		consume(Token::Type::RightRoundBracket);

		StatementPtr true_branch = parse_compound_statement();
		StatementPtr false_branch = nullptr;
		if (m_current_token.type == Token::Type::Else)
		{
			consume(Token::Type::Else);
			false_branch = parse_compound_statement();
		}

		return std::make_unique<IfStatement>(
			std::move(condition), std::move(true_branch), std::move(false_branch));
	}

	StatementPtr Parser::parse_print_statement()
	{
		consume(Token::Type::Print);
		consume(Token::Type::LeftRoundBracket);

		ExpressionPtr argument = parse_binary_expression(0);

		consume(Token::Type::RightRoundBracket);

		return std::make_unique<PrintStatement>(std::move(argument));
	}

	StatementPtr Parser::parse_return_statement()
	{
		consume(Token::Type::Return);

		ExpressionPtr expression = parse_binary_expression(0);

		return std::make_unique<ReturnStatement>(std::move(expression));
	}

	StatementPtr Parser::parse_while_statement()
	{
		consume(Token::Type::While);

		consume(Token::Type::LeftRoundBracket);
		ExpressionPtr condition = parse_binary_expression(0);
		consume(Token::Type::RightRoundBracket);

		StatementPtr body = parse_compound_statement();

		return std::make_unique<WhileStatement>(
			std::move(condition), std::move(body));
	}

	bool Parser::match(Token::Type token_type) const
	{
		const Token::Type type = m_saved_token.type == Token::Type::None
															 ? m_current_token.type
															 : m_saved_token.type;
		return type == token_type;
	}

	Token Parser::consume()
	{
		if (m_saved_token.type != Token::Type::None)
		{
			m_saved_token.type = Token::Type::None;
			return m_saved_token;
		}

		Token old_token = m_current_token;
		m_current_token = m_scanner.next_token();
		return old_token;
	}

	Token Parser::consume(Token::Type token_type)
	{
		if (!match(token_type))
		{
			const Token::SourceLocation location = m_current_token.location;
			const std::string line_string = std::to_string(location.line);
			const std::string column_string = std::to_string(location.column);
			const std::string file = m_file + ":" + line_string + ":" + column_string;
			Logger::file_error(
				file,
				"Unexpected token '{}', expected '{}'\n",
				m_current_token.type,
				token_type);
			std::abort();
		}

		return consume();
	}

	Type Parser::map_type(Token::Type token_type) const
	{
		switch (token_type)
		{
		case Token::Type::Bool:
			return Type::Bool;
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
		case Token::Type::ISize:
			return Type::ISize;
		case Token::Type::USize:
			return Type::USize;
		case Token::Type::Void:
			return Type::Void;
		default:
			expected("Type");
			break;
		}

		return Type::None;
	}

	uint8_t Parser::map_precedence(Token::Type token_type) const
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

	void Parser::save_token(Token token)
	{
		if (m_saved_token.type != Token::Type::None)
		{
			return;
		}

		m_saved_token = std::move(token);
	}

	void Parser::expected(std::string_view expected) const
	{
		const Token::SourceLocation location = m_current_token.location;
		const std::string line_string = std::to_string(location.line);
		const std::string column_string = std::to_string(location.column);
		const std::string file = m_file + ":" + line_string + ":" + column_string;
		Logger::file_error(
			file,
			"Unexpected token '{}', expected '{}'\n",
			m_current_token.type,
			expected);
	}
} // namespace Hyper
