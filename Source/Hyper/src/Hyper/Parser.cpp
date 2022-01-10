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
#include "Hyper/Ast/Expressions/CastExpression.hpp"
#include "Hyper/Ast/Expressions/ConditionalExpression.hpp"
#include "Hyper/Ast/Expressions/IdentifierExpression.hpp"
#include "Hyper/Ast/Expressions/UnaryExpression.hpp"
#include "Hyper/Ast/Literals/BoolLiteral.hpp"
#include "Hyper/Ast/Literals/IntegerLiteral.hpp"
#include "Hyper/Ast/Literals/StringLiteral.hpp"
#include "Hyper/Ast/Statements/AssignStatement.hpp"
#include "Hyper/Ast/Statements/CompoundAssignStatement.hpp"
#include "Hyper/Ast/Statements/CompoundStatement.hpp"
#include "Hyper/Ast/Statements/ExpressionStatement.hpp"
#include "Hyper/Ast/Statements/IfStatement.hpp"
#include "Hyper/Ast/Statements/ReturnStatement.hpp"
#include "Hyper/Ast/Statements/WhileStatement.hpp"
#include "Hyper/Diagnostics.hpp"
#include "Hyper/Formatter.hpp"
#include "Hyper/Lexer.hpp"

namespace Hyper
{
	Parser::Parser(Diagnostics &diagnostics, Lexer &lexer, std::string file)
		: m_diagnostics(diagnostics)
		, m_lexer(lexer)
		, m_file(std::move(file))
	{
	}

	AstPtr Parser::parse_tree()
	{
		consume();
		return parse_translation_unit_declaration();
	}

	DeclarationPtr Parser::parse_function_declaration()
	{
		const Position start = consume(Token::Type::Function).range.start;

		const Token identifier_token = consume(Token::Type::Identifier);

		consume(Token::Type::RoundLeftBracket);

		// TODO: Adding arguments
		DeclarationList arguments = {};

		consume(Token::Type::RoundRightBracket);
		consume(Token::Type::Arrow);

		const Type return_type = consume_type();

		auto body = parse_compound_statement();

		const SourceRange range = {
			.start = start,
			.end = body->range().end,
		};

		const Identifier identifier = {
			.value = identifier_token.value,
			.range = identifier_token.range,
		};

		return std::make_unique<FunctionDeclaration>(
			range, identifier, std::move(arguments), return_type, std::move(body));
	}

	DeclarationPtr Parser::parse_translation_unit_declaration()
	{
		DeclarationList declarations = {};
		while (!match(Token::Type::Eof))
		{
			// TODO: Adding import declaration
			declarations.emplace_back(parse_function_declaration());
		}

		const SourceRange range = {
			.start = declarations.front()->range().start,
			.end = declarations.back()->range().end,
		};

		return std::make_unique<TranslationUnitDeclaration>(
			range, m_file, std::move(declarations));
	}

	DeclarationPtr Parser::parse_variable_declaration()
	{
		const Position start = consume(Token::Type::Let).range.start;

		const Token identifier_token = consume(Token::Type::Identifier);

		consume(Token::Type::Colon);

		VariableDeclaration::MutableState mutable_state =
			VariableDeclaration::MutableState::No;
		if (match(Token::Type::Mutable))
		{
			consume();
			mutable_state = VariableDeclaration::MutableState::Yes;
		}

		const Type type = consume_type();

		auto expression = [this]() -> ExpressionPtr
		{
			if (match(Token::Type::Assign))
			{
				consume(Token::Type::Assign);
				return parse_binary_expression(0);
			}

			return nullptr;
		}();

		const Position end =
			expression == nullptr ? type.range.end : expression->range().end;

		const SourceRange range = {
			.start = start,
			.end = end,
		};

		const Identifier identifier = {
			.value = identifier_token.value,
			.range = identifier_token.range,
		};

		return std::make_unique<VariableDeclaration>(
			range, identifier, mutable_state, type, std::move(expression));
	}

	ExpressionPtr Parser::parse_prefix_expression()
	{
		const Token operation_token = current_token();
		const UnaryExpression::Operation::Kind kind = [&]()
		{
			switch (operation_token.type)
			{
			case Token::Type::Minus:
				return UnaryExpression::Operation::Kind::Negative;
			case Token::Type::Increment:
				return UnaryExpression::Operation::Kind::PreIncrement;
			case Token::Type::Decrement:
				return UnaryExpression::Operation::Kind::PreDecrement;
			case Token::Type::LogicalNot:
				return UnaryExpression::Operation::Kind::Not;
			case Token::Type::BitwiseNot:
				return UnaryExpression::Operation::Kind::Inverse;
			default:
				return UnaryExpression::Operation::Kind::Invalid;
			}
		}();

		if (kind != UnaryExpression::Operation::Kind::Invalid)
		{
			consume();

			auto expression = parse_primary_expression();

			const SourceRange range = {
				.start = operation_token.range.start,
				.end = expression->range().end,
			};

			const UnaryExpression::Operation operation = {
				.kind = kind,
				.range = operation_token.range,
			};

			return std::make_unique<UnaryExpression>(
				range, operation, std::move(expression));
		}

		return parse_primary_expression();
	}

	ExpressionPtr Parser::parse_postfix_expression()
	{
		const Token identifier_token = consume(Token::Type::Identifier);
		if (match(Token::Type::RoundLeftBracket))
		{
			save_token(identifier_token);
			return parse_call_expression();
		}

		save_token(identifier_token);

		auto expression = parse_identifier_expression();

		const Token operation_token = current_token();
		const UnaryExpression::Operation::Kind kind = [&]()
		{
			switch (operation_token.type)
			{
			case Token::Type::Increment:
				return UnaryExpression::Operation::Kind::PostIncrement;
			case Token::Type::Decrement:
				return UnaryExpression::Operation::Kind::PostDecrement;
			default:
				return UnaryExpression::Operation::Kind::Invalid;
			}
		}();

		if (kind != UnaryExpression::Operation::Kind::Invalid)
		{
			consume();

			const SourceRange range = {
				.start = identifier_token.range.start,
				.end = expression->range().end,
			};

			const UnaryExpression::Operation operation = {
				.kind = kind,
				.range = operation_token.range,
			};

			return std::make_unique<UnaryExpression>(
				range, operation, std::move(expression));
		}

		return expression;
	}

	ExpressionPtr Parser::parse_paren_expression()
	{
		consume(Token::Type::RoundLeftBracket);

		auto expression = parse_binary_expression(0);

		consume(Token::Type::RoundRightBracket);

		return expression;
	}

	ExpressionPtr Parser::parse_primary_expression()
	{
		switch (current_token().type)
		{
		case Token::Type::Identifier:
			return parse_postfix_expression();
		case Token::Type::BoolLiteral:
			return parse_bool_literal();
		case Token::Type::IntegerLiteral:
			return parse_integer_literal();
		case Token::Type::StringLiteral:
			return parse_string_literal();
		case Token::Type::RoundLeftBracket:
			return parse_paren_expression();
		default:
			break;
		}

		return nullptr;
	}

	ExpressionPtr Parser::parse_binary_expression(uint8_t precedence)
	{
		auto left = parse_prefix_expression();

		Token token = current_token();
		if (token.type == Token::Type::As)
		{
			consume();

			const Type type = consume_type();

			const SourceRange range = {
				.start = left->range().start,
				.end = type.range.end,
			};

			left = std::make_unique<CastExpression>(range, std::move(left), type);

			token = current_token();
		}

		if (match(Token::Type::Semicolon) || match(Token::Type::RoundRightBracket))
		{
			return left;
		}

		while (map_precedence(token.type) > precedence)
		{
			consume();

			auto right = parse_binary_expression(map_precedence(token.type));

			if (token.type == Token::Type::QuestionMark && match(Token::Type::Colon))
			{
				consume();

				auto temp = parse_binary_expression(map_precedence(token.type));

				const SourceRange range = {
					.start = left->range().start,
					.end = temp->range().end,
				};

				return std::make_unique<ConditionalExpression>(
					range, std::move(left), std::move(right), std::move(temp));
			}

			const BinaryExpression::Operation::Kind kind = [&]()
			{
				switch (token.type)
				{
				case Token::Type::Plus:
					return BinaryExpression::Operation::Kind::Addition;
				case Token::Type::Minus:
					return BinaryExpression::Operation::Kind::Subtraction;
				case Token::Type::Star:
					return BinaryExpression::Operation::Kind::Multiplication;
				case Token::Type::Slash:
					return BinaryExpression::Operation::Kind::Division;
				case Token::Type::Percent:
					return BinaryExpression::Operation::Kind::Modulo;
				case Token::Type::BitwiseAnd:
					return BinaryExpression::Operation::Kind::BitwiseAnd;
				case Token::Type::BitwiseOr:
					return BinaryExpression::Operation::Kind::BitwiseOr;
				case Token::Type::BitwiseXor:
					return BinaryExpression::Operation::Kind::BitwiseXor;
				case Token::Type::LeftShift:
					return BinaryExpression::Operation::Kind::LeftShift;
				case Token::Type::RightShift:
					return BinaryExpression::Operation::Kind::RightShift;
				case Token::Type::LogicalAnd:
					return BinaryExpression::Operation::Kind::LogicalAnd;
				case Token::Type::LogicalOr:
					return BinaryExpression::Operation::Kind::LogicalOr;
				case Token::Type::Equal:
					return BinaryExpression::Operation::Kind::Equal;
				case Token::Type::NotEqual:
					return BinaryExpression::Operation::Kind::NotEqual;
				case Token::Type::LessThan:
					return BinaryExpression::Operation::Kind::LessThan;
				case Token::Type::GreaterThan:
					return BinaryExpression::Operation::Kind::GreaterThan;
				case Token::Type::LessEqual:
					return BinaryExpression::Operation::Kind::LessEqual;
				case Token::Type::GreaterEqual:
					return BinaryExpression::Operation::Kind::GreaterEqual;
				default:
				{
					const Token this_token = current_token();
					const std::string error =
						Formatter::format("expected operator, found '{}'", token.value);
					m_diagnostics.error(token.range, error);
				}
				}
			}();

			const SourceRange range = {
				.start = left->range().start,
				.end = right->range().end,
			};

			const BinaryExpression::Operation operation = {
				.kind = kind,
				.range = token.range,
			};

			left = std::make_unique<BinaryExpression>(
				range, operation, std::move(left), std::move(right));
			token.type = current_token().type;
			if (
				match(Token::Type::Semicolon) || match(Token::Type::RoundRightBracket))
			{
				break;
			}
		}

		return left;
	}

	ExpressionPtr Parser::parse_call_expression()
	{
		const Token identifier_token = consume(Token::Type::Identifier);

		consume(Token::Type::RoundLeftBracket);

		ExpressionList arguments = {};

		const Position end = consume(Token::Type::RoundRightBracket).range.end;

		const SourceRange range = {
			.start = identifier_token.range.start,
			.end = end,
		};

		const Identifier identifier = {
			.value = identifier_token.value,
			.range = identifier_token.range,
		};

		return std::make_unique<CallExpression>(
			range, identifier, std::move(arguments));
	}

	ExpressionPtr Parser::parse_identifier_expression()
	{
		const Token identifier_token = consume(Token::Type::Identifier);
		const Identifier identifier = {
			.value = identifier_token.value,
			.range = identifier_token.range,
		};

		return std::make_unique<IdentifierExpression>(identifier.range, identifier);
	}

	LiteralPtr Parser::parse_bool_literal()
	{
		const Token boolean = consume(Token::Type::BoolLiteral);
		return std::make_unique<BoolLiteral>(
			boolean.range, boolean.value == "true");
	}

	LiteralPtr Parser::parse_integer_literal()
	{
		const Token integer = consume(Token::Type::IntegerLiteral);
		return std::make_unique<IntegerLiteral>(integer.range, integer.value);
	}

	LiteralPtr Parser::parse_string_literal()
	{
		const Token string = consume(Token::Type::StringLiteral);
		return std::make_unique<StringLiteral>(string.range, string.value);
	}

	StatementPtr Parser::parse_statement()
	{
		switch (current_token().type)
		{
		case Token::Type::Increment:
		case Token::Type::Decrement:
			return parse_expression_statement(parse_prefix_expression());
		case Token::Type::Identifier:
			return parse_assign_statement();
		case Token::Type::If:
			return parse_if_statement();
		case Token::Type::Let:
			return parse_variable_declaration();
		case Token::Type::Return:
			return parse_return_statement();
		case Token::Type::While:
			return parse_while_statement();
		default:
			break;
		}

		return nullptr;
	}

	StatementPtr Parser::parse_assign_statement()
	{
		const Token identifier_token = consume(Token::Type::Identifier);
		if (match(Token::Type::RoundLeftBracket))
		{
			save_token(identifier_token);
			return parse_expression_statement(parse_call_expression());
		}

		// TODO: Postfix can be changed to binary if binary returns null.
		if (match(Token::Type::Increment) || match(Token::Type::Decrement))
		{
			save_token(identifier_token);
			return parse_expression_statement(parse_postfix_expression());
		}

		switch (current_token().type)
		{
		case Token::Type::PlusEqual:
		case Token::Type::MinusEqual:
		case Token::Type::StarEqual:
		case Token::Type::SlashEqual:
		case Token::Type::PercentEqual:
		case Token::Type::BitwiseAndEqual:
		case Token::Type::BitwiseOrEqual:
		case Token::Type::BitwiseXorEqual:
		case Token::Type::LeftShiftEqual:
		case Token::Type::RightShiftEqual:
			save_token(identifier_token);
			return parse_compound_assign_statement();
		default:
			break;
		}

		consume(Token::Type::Assign);

		auto expression = parse_binary_expression(0);

		const SourceRange range = {
			.start = identifier_token.range.start,
			.end = expression->range().end,
		};

		const Identifier identifier = {
			.value = identifier_token.value,
			.range = identifier_token.range,
		};

		return std::make_unique<AssignStatement>(
			range, identifier, std::move(expression));
	}

	StatementPtr Parser::parse_compound_statement()
	{
		const Position start = consume(Token::Type::CurlyLeftBracket).range.start;

		StatementList statements = {};
		while (true)
		{
			auto statement = parse_statement();
			if (statement != nullptr)
			{
				if (
					statement->class_category() == AstNode::Category::AssignStatement ||
					statement->class_category() ==
						AstNode::Category::CompoundAssignStatement ||
					statement->class_category() ==
						AstNode::Category::ExpressionStatement ||
					statement->class_category() == AstNode::Category::ReturnStatement ||
					statement->class_category() == AstNode::Category::VariableDeclaration)
				{
					consume(Token::Type::Semicolon);
				}

				statements.emplace_back(std::move(statement));
			}

			if (match(Token::Type::CurlyRightBracket))
			{
				break;
			}
		}

		const Position end = consume(Token::Type::CurlyRightBracket).range.end;

		const SourceRange range = {
			.start = start,
			.end = end,
		};

		return std::make_unique<CompoundStatement>(range, std::move(statements));
	}

	StatementPtr Parser::parse_compound_assign_statement()
	{
		const Token identifier_token = consume(Token::Type::Identifier);
		const CompoundAssignStatement::Operation operation = [this]()
		{
			switch (current_token().type)
			{
			case Token::Type::PlusEqual:
				return CompoundAssignStatement::Operation::Addition;
			case Token::Type::MinusEqual:
				return CompoundAssignStatement::Operation::Subtraction;
			case Token::Type::StarEqual:
				return CompoundAssignStatement::Operation::Multiplication;
			case Token::Type::SlashEqual:
				return CompoundAssignStatement::Operation::Division;
			case Token::Type::PercentEqual:
				return CompoundAssignStatement::Operation::Modulo;
			case Token::Type::BitwiseAndEqual:
				return CompoundAssignStatement::Operation::BitwiseAnd;
			case Token::Type::BitwiseOrEqual:
				return CompoundAssignStatement::Operation::BitwiseOr;
			case Token::Type::BitwiseXorEqual:
				return CompoundAssignStatement::Operation::BitwiseXor;
			case Token::Type::LeftShiftEqual:
				return CompoundAssignStatement::Operation::LeftShift;
			case Token::Type::RightShiftEqual:
				return CompoundAssignStatement::Operation::RightShift;
			default:
				return CompoundAssignStatement::Operation::Invalid;
			}
		}();

		if (operation == CompoundAssignStatement::Operation::Invalid)
		{
			return nullptr;
		}

		consume();

		auto expression = parse_binary_expression(0);

		const SourceRange range = {
			.start = identifier_token.range.start,
			.end = expression->range().end,
		};

		const Identifier identifier = {
			.value = identifier_token.value,
			.range = identifier_token.range,
		};

		return std::make_unique<CompoundAssignStatement>(
			range, identifier, operation, std::move(expression));
	}

	StatementPtr Parser::parse_expression_statement(ExpressionPtr expression)
	{
		return std::make_unique<ExpressionStatement>(
			expression->range(), std::move(expression));
	}

	StatementPtr Parser::parse_if_statement()
	{
		const Position start = consume(Token::Type::If).range.start;
		consume(Token::Type::RoundLeftBracket);

		auto condition = parse_binary_expression(0);

		consume(Token::Type::RoundRightBracket);

		auto true_body = parse_compound_statement();
		auto false_body = [this]() -> StatementPtr
		{
			if (current_token().type != Token::Type::Else)
			{
				return nullptr;
			}

			consume();
			return parse_compound_statement();
		}();

		const Position end =
			false_body == nullptr ? true_body->range().end : false_body->range().end;

		const SourceRange range = {
			.start = start,
			.end = end,
		};

		return std::make_unique<IfStatement>(
			range, std::move(condition), std::move(true_body), std::move(false_body));
	}

	StatementPtr Parser::parse_return_statement()
	{
		const SourceRange return_range = consume(Token::Type::Return).range;

		if (match(Token::Type::Semicolon))
		{
			return std::make_unique<ReturnStatement>(return_range, nullptr);
		}

		auto expression = parse_binary_expression(0);

		const SourceRange range = {
			.start = return_range.start,
			.end = expression->range().end,
		};

		return std::make_unique<ReturnStatement>(range, std::move(expression));
	}

	StatementPtr Parser::parse_while_statement()
	{
		const Position start = consume(Token::Type::While).range.start;
		consume(Token::Type::RoundLeftBracket);

		auto condition = parse_binary_expression(0);

		consume(Token::Type::RoundRightBracket);

		auto body = parse_compound_statement();

		const SourceRange range = {
			.start = start,
			.end = body->range().end,
		};

		return std::make_unique<WhileStatement>(
			range, std::move(condition), std::move(body));
	}

	Token Parser::current_token() const noexcept
	{
		const bool invalid = m_saved_token.type == Token::Type::Invalid;
		return invalid ? m_current_token : m_saved_token;
	}

	void Parser::save_token(Token token)
	{
		m_saved_token = std::move(token);
	}

	Token Parser::consume() noexcept
	{
		Token old_token = current_token();
		m_last_token = old_token;
		if (m_saved_token.type != Token::Type::Invalid)
		{
			m_saved_token.type = Token::Type::Invalid;
			return old_token;
		}

		m_current_token = m_lexer.next_token();
		return old_token;
	}

	Token Parser::consume(Token::Type token_type) noexcept
	{
		if (!match(token_type))
		{
			const Token &token = current_token();
			const Position start_position = [&]()
			{
				if (token_type != Token::Type::Semicolon)
				{
					return token.range.start;
				}

				return m_last_token.range.start;
			}();

			const Position end_position = token.range.end;
			const SourceRange source_range = {
				.start = start_position,
				.end = end_position,
			};

			const std::string error = Formatter::format(
				"expected '{}', found '{}'", map_value(token_type), token.value);
			m_diagnostics.error(source_range, error);
		}

		return consume();
	}

	bool Parser::match(Token::Type token_type) const noexcept
	{
		return current_token().type == token_type;
	}

	Type Parser::consume_type()
	{
		auto type = [this]() -> Type
		{
			switch (current_token().type)
			{
			case Token::Type::Bool:
				return { "bool", Type::Kind::Bool, current_token().range };
			case Token::Type::Int8:
				return { "i8", Type::Kind::Int8, current_token().range };
			case Token::Type::Int16:
				return { "i16", Type::Kind::Int16, current_token().range };
			case Token::Type::Int32:
				return { "i32", Type::Kind::Int32, current_token().range };
			case Token::Type::Int64:
				return { "i64", Type::Kind::Int64, current_token().range };
			case Token::Type::Uint8:
				return { "u8", Type::Kind::Uint8, current_token().range };
			case Token::Type::Uint16:
				return { "u16", Type::Kind::Uint16, current_token().range };
			case Token::Type::Uint32:
				return { "u32", Type::Kind::Uint32, current_token().range };
			case Token::Type::Uint64:
				return { "u64", Type::Kind::Uint64, current_token().range };
			case Token::Type::ISize:
				return { "isize", Type::Kind::ISize, current_token().range };
			case Token::Type::USize:
				return { "usize", Type::Kind::USize, current_token().range };
			case Token::Type::Float32:
				return { "f32", Type::Kind::Float32, current_token().range };
			case Token::Type::Float64:
				return { "f64", Type::Kind::Float64, current_token().range };
			case Token::Type::String:
				return { "string", Type::Kind::String, current_token().range };
			case Token::Type::Void:
				return { "void", Type::Kind::Void, current_token().range };
			case Token::Type::Identifier:
				return {
					current_token().value,
					Type::Kind::UserDefined,
					current_token().range,
				};
			default:
			{
				const Token token = current_token();
				const std::string error =
					Formatter::format("expected type, found '{}'", token.value);
				m_diagnostics.error(token.range, error);
			}
			}
		}();

		consume();

		return type;
	}

	uint8_t Parser::map_precedence(Token::Type token_type) const noexcept
	{
		switch (token_type)
		{
		case Token::Type::QuestionMark:
			return 10;
		case Token::Type::LogicalOr:
			return 20;
		case Token::Type::LogicalAnd:
			return 30;
		case Token::Type::BitwiseOr:
			return 40;
		case Token::Type::BitwiseXor:
			return 50;
		case Token::Type::BitwiseAnd:
			return 60;
		case Token::Type::Equal:
		case Token::Type::NotEqual:
			return 70;
		case Token::Type::LessThan:
		case Token::Type::GreaterThan:
		case Token::Type::LessEqual:
		case Token::Type::GreaterEqual:
			return 80;
		case Token::Type::LeftShift:
		case Token::Type::RightShift:
			return 90;
		case Token::Type::Plus:
		case Token::Type::Minus:
			return 100;
		case Token::Type::Star:
		case Token::Type::Slash:
		case Token::Type::Percent:
			return 110;
		case Token::Type::As:
		case Token::Type::BitwiseNot:
			return 120;
		default:
			break;
		}

		return 0;
	}

	std::string Parser::map_value(Token::Type token_type) const noexcept
	{
		switch (token_type)
		{
		case Token::Type::Eof:
			return "EOF";
		case Token::Type::Arrow:
			return "->";
		case Token::Type::Dot:
			return ".";
		case Token::Type::Colon:
			return ":";
		case Token::Type::Identifier:
			return "identifier";
		case Token::Type::Semicolon:
			return ";";
		case Token::Type::Assign:
			return "=";
		case Token::Type::PlusEqual:
			return "!=";
		case Token::Type::MinusEqual:
			return "-=";
		case Token::Type::StarEqual:
			return "*=";
		case Token::Type::SlashEqual:
			return "/=";
		case Token::Type::PercentEqual:
			return "%=";
		case Token::Type::BitwiseAndEqual:
			return "&=";
		case Token::Type::BitwiseOrEqual:
			return "|=";
		case Token::Type::BitwiseXorEqual:
			return "^=";
		case Token::Type::LeftShiftEqual:
			return "<<=";
		case Token::Type::RightShiftEqual:
			return ">>=";
		case Token::Type::Increment:
			return "++";
		case Token::Type::Decrement:
			return "--";
		case Token::Type::Plus:
			return "+";
		case Token::Type::Minus:
			return "-";
		case Token::Type::Star:
			return "*";
		case Token::Type::Slash:
			return "/";
		case Token::Type::Percent:
			return "%";
		case Token::Type::BitwiseAnd:
			return "&";
		case Token::Type::BitwiseOr:
			return "|";
		case Token::Type::BitwiseNot:
			return "~";
		case Token::Type::BitwiseXor:
			return "^";
		case Token::Type::LeftShift:
			return "<<";
		case Token::Type::RightShift:
			return ">>";
		case Token::Type::LogicalNot:
			return "!";
		case Token::Type::LogicalAnd:
			return "&&";
		case Token::Type::LogicalOr:
			return "||";
		case Token::Type::Equal:
			return "==";
		case Token::Type::NotEqual:
			return "!=";
		case Token::Type::LessThan:
			return "<";
		case Token::Type::GreaterThan:
			return ">";
		case Token::Type::LessEqual:
			return "<=";
		case Token::Type::GreaterEqual:
			return ">=";
		case Token::Type::QuestionMark:
			return "?";
		case Token::Type::CurlyLeftBracket:
			return "{";
		case Token::Type::CurlyRightBracket:
			return "}";
		case Token::Type::SquareLeftBracket:
			return "[";
		case Token::Type::SquareRightBracket:
			return "]";
		case Token::Type::RoundLeftBracket:
			return "(";
		case Token::Type::RoundRightBracket:
			return ")";
		case Token::Type::Break:
			return "break";
		case Token::Type::Else:
			return "else";
		case Token::Type::For:
			return "for";
		case Token::Type::If:
			return "if";
		case Token::Type::Return:
			return "return";
		case Token::Type::While:
			return "while";
		case Token::Type::Export:
			return "export";
		case Token::Type::Import:
			return "import";
		case Token::Type::Function:
			return "fn";
		case Token::Type::Let:
			return "let";
		case Token::Type::Mutable:
			return "mutable";
		case Token::Type::Struct:
			return "struct";
		case Token::Type::Bool:
			return "bool";
		case Token::Type::Int8:
			return "i8";
		case Token::Type::Int16:
			return "";
		case Token::Type::Int32:
			return "i32";
		case Token::Type::Int64:
			return "i64";
		case Token::Type::Uint8:
			return "u8";
		case Token::Type::Uint16:
			return "u16";
		case Token::Type::Uint32:
			return "u32";
		case Token::Type::Uint64:
			return "u64";
		case Token::Type::ISize:
			return "isize";
		case Token::Type::USize:
			return "usize";
		case Token::Type::Float32:
			return "f32";
		case Token::Type::Float64:
			return "f64";
		case Token::Type::String:
			return "string";
		case Token::Type::Void:
			return "void";
		case Token::Type::BoolLiteral:
			return "bool literal";
		case Token::Type::IntegerLiteral:
			return "integer literal";
		case Token::Type::StringLiteral:
			return "string literal";
		default:
			break;
		}

		return "";
	}
} // namespace Hyper
