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

namespace Hyper
{
	Parser::Parser(std::string file, Scanner &scanner, bool debug_mode)
		: m_file(std::move(file))
		, m_scanner(scanner)
		, m_debug_mode(debug_mode)
	{
		consume();
	}

	AstPtr Parser::parse_tree()
	{
		AstPtr node = parse_translation_unit_declaration();

		if (m_debug_mode)
		{
			node->dump_tree(m_file);
		}

		return node;
	}

	DeclarationPtr Parser::parse_function_declaration()
	{
		consume(Token::Type::Function);

		const std::string name = consume(Token::Type::Identifier).value;

		consume(Token::Type::LeftRoundBracket);

		std::vector<DeclarationPtr> arguments = {};

		consume(Token::Type::RightRoundBracket);
		consume(Token::Type::RightArrow);

		const DataType return_type = map_type(m_current_token.type);
		consume();

		StatementPtr body = parse_compound_statement();

		FunctionDeclaration::CreateInfo create_info = {
			.name = name,
			.arguments = std::move(arguments),
			.return_type = return_type,
			.body = std::move(body),
		};

		DeclarationPtr declaration =
			std::make_unique<FunctionDeclaration>(std::move(create_info));
		debug_parse(*declaration);

		return declaration;
	}

	DeclarationPtr Parser::parse_translation_unit_declaration()
	{
		std::vector<StatementPtr> statements = {};
		while (!match(Token::Type::Eof))
		{
			StatementPtr statement = parse_statement();
			statements.push_back(std::move(statement));
		}

		TranslationUnitDeclaration::CreateInfo create_info = {
			.file = m_file,
			.statements = std::move(statements),
		};

		DeclarationPtr declaration =
			std::make_unique<TranslationUnitDeclaration>(std::move(create_info));
		debug_parse(*declaration);

		return declaration;
	}

	DeclarationPtr Parser::parse_variable_declaration()
	{
		consume(Token::Type::Let);

		const std::string name = consume(Token::Type::Identifier).value;

		consume(Token::Type::Colon);

		bool is_immutable = true;
		if (match(Token::Type::Mutable))
		{
			consume();
			is_immutable = false;
		}

		const DataType type = map_type(m_current_token.type);
		consume();

		consume(Token::Type::Semicolon);

		VariableDeclaration::CreateInfo create_info = {
			.name = name,
			.type = type,
			.is_immutable = is_immutable,
		};

		DeclarationPtr declaration =
			std::make_unique<VariableDeclaration>(std::move(create_info));
		debug_parse(*declaration);

		return declaration;
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

		HYPER_UNREACHABLE();
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

			BinaryExpression::CreateInfo create_info = {
				.operation = operation,
				.left = std::move(left),
				.right = std::move(right),
			};

			left = std::make_unique<BinaryExpression>(std::move(create_info));

			token_type = m_current_token.type;
			if (
				token_type == Token::Type::Semicolon ||
				token_type == Token::Type::RightRoundBracket)
			{
				break;
			}
		}

		debug_parse(*left);

		return left;
	}

	ExpressionPtr Parser::parse_call_expression()
	{
		std::string function = consume(Token::Type::Identifier).value;

		consume(Token::Type::LeftRoundBracket);

		std::vector<ExpressionPtr> arguments = {};

		consume(Token::Type::RightRoundBracket);

		CallExpression::CreateInfo create_info = {
			.function = function,
			.arguments = std::move(arguments),
		};

		ExpressionPtr expression =
			std::make_unique<CallExpression>(std::move(create_info));
		debug_parse(*expression);

		return expression;
	}

	ExpressionPtr Parser::parse_identifier_expression()
	{
		const Token identifier_token = consume(Token::Type::Identifier);
		if (match(Token::Type::LeftRoundBracket))
		{
			save_token(identifier_token);
			return parse_call_expression();
		}

		IdentifierExpression::CreateInfo create_info = {
			.identifier = identifier_token.value,
		};

		ExpressionPtr expression =
			std::make_unique<IdentifierExpression>(std::move(create_info));
		debug_parse(*expression);

		return expression;
	}

	LiteralPtr Parser::parse_numeric_literal()
	{
		bool is_signed = false;
		if (match(Token::Type::Minus))
		{
			consume();
			is_signed = true;
		}

		uint64_t value = std::stoull(consume(Token::Type::NumericLiteral).value);
		if (is_signed)
		{
			value += static_cast<uint64_t>(std::numeric_limits<int64_t>::min());
		}

		NumericLiteral::CreateInfo create_info = {
			.value = value,
			.is_signed = is_signed,
		};

		LiteralPtr literal = std::make_unique<NumericLiteral>(create_info);
		debug_parse(*literal);

		return literal;
	}

	LiteralPtr Parser::parse_string_literal()
	{
		std::string value = consume(Token::Type::StringLiteral).value;

		StringLiteral::CreateInfo create_info = {
			.value = value,
		};

		LiteralPtr literal =
			std::make_unique<StringLiteral>(std::move(create_info));
		debug_parse(*literal);

		return literal;
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

		HYPER_UNREACHABLE();
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

		AssignStatement::CreateInfo create_info = {
			.identifier = identifier_token.value,
			.expression = std::move(expression),
		};

		StatementPtr statement =
			std::make_unique<AssignStatement>(std::move(create_info));
		debug_parse(*statement);

		return statement;
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

		CompoundStatement::CreateInfo create_info = {
			.statements = std::move(statements),
		};

		StatementPtr statement =
			std::make_unique<CompoundStatement>(std::move(create_info));
		debug_parse(*statement);

		return statement;
	}

	StatementPtr Parser::parse_expression_statement(ExpressionPtr expression)
	{
		ExpressionStatement::CreateInfo create_info = {
			.expression = std::move(expression),
		};

		StatementPtr statement =
			std::make_unique<ExpressionStatement>(std::move(create_info));
		debug_parse(*statement);

		return statement;
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

		ForStatement::CreateInfo create_info = {
			.pre_operation = std::move(pre_operation),
			.condition = std::move(condition),
			.post_operation = std::move(post_operation),
			.body = std::move(body),
		};

		StatementPtr statement =
			std::make_unique<ForStatement>(std::move(create_info));
		debug_parse(*statement);

		return statement;
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

		IfStatement::CreateInfo create_info = {
			.condition = std::move(condition),
			.true_branch = std::move(true_branch),
			.false_branch = std::move(false_branch),
		};

		StatementPtr statement =
			std::make_unique<IfStatement>(std::move(create_info));
		debug_parse(*statement);

		return statement;
	}

	StatementPtr Parser::parse_print_statement()
	{
		consume(Token::Type::Print);
		consume(Token::Type::LeftRoundBracket);

		ExpressionPtr expression = parse_binary_expression(0);

		consume(Token::Type::RightRoundBracket);

		PrintStatement::CreateInfo create_info = {
			.expression = std::move(expression),
		};

		StatementPtr statement =
			std::make_unique<PrintStatement>(std::move(create_info));
		debug_parse(*statement);

		return statement;
	}

	StatementPtr Parser::parse_return_statement()
	{
		consume(Token::Type::Return);

		ExpressionPtr expression = parse_binary_expression(0);

		ReturnStatement::CreateInfo create_info = {
			.expression = std::move(expression),
		};

		StatementPtr statement =
			std::make_unique<ReturnStatement>(std::move(create_info));
		debug_parse(*statement);

		return statement;
	}

	StatementPtr Parser::parse_while_statement()
	{
		consume(Token::Type::While);

		consume(Token::Type::LeftRoundBracket);
		ExpressionPtr condition = parse_binary_expression(0);
		consume(Token::Type::RightRoundBracket);

		StatementPtr body = parse_compound_statement();

		WhileStatement::CreateInfo create_info = {
			.condition = std::move(condition),
			.body = std::move(body),
		};

		StatementPtr statement =
			std::make_unique<WhileStatement>(std::move(create_info));
		debug_parse(*statement);

		return statement;
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

	DataType Parser::map_type(Token::Type token_type) const
	{
		switch (token_type)
		{
		case Token::Type::Bool:
			return DataType::Bool;
		case Token::Type::Int8:
			return DataType::Int8;
		case Token::Type::Int16:
			return DataType::Int16;
		case Token::Type::Int32:
			return DataType::Int32;
		case Token::Type::Int64:
			return DataType::Int64;
		case Token::Type::Uint8:
			return DataType::Uint8;
		case Token::Type::Uint16:
			return DataType::Uint16;
		case Token::Type::Uint32:
			return DataType::Uint32;
		case Token::Type::Uint64:
			return DataType::Uint64;
		case Token::Type::ISize:
			return DataType::ISize;
		case Token::Type::USize:
			return DataType::USize;
		case Token::Type::Void:
			return DataType::Void;
		default:
			expected("DataType");
			break;
		}

		std::abort();
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

	void Parser::debug_parse(const AstNode &node) const
	{
		if (!m_debug_mode)
		{
			return;
		}

		Logger::file_info(
			m_file, "Parsing {} {}\n", node.class_name(), node.class_description());
	}
} // namespace Hyper
