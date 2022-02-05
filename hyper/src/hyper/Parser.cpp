/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/parser.hpp"

#include "hyper/ast/ast.hpp"
#include "hyper/lexer.hpp"

namespace hyper
{
	Parser::Parser(
		const Diagnostics &diagnostics,
		const std::vector<Token> &tokens,
		std::string file)
		: m_diagnostics(diagnostics)
		, m_tokens(tokens)
		, m_file(std::move(file))
	{
	}

	AstNodePtr Parser::parse()
	{
		return parse_translation_unit_declaration();
	}

	DeclarationPtr Parser::parse_function_declaration()
	{
		const SourceRange function_range =
			consume(Token::Type::Function).source_range();
		const Identifier identifier = consume_identifier();

		consume(Token::Type::RoundLeftBracket);

		// TODO: Adding arguments
		std::vector<DeclarationPtr> arguments = {};

		consume(Token::Type::RoundRightBracket);
		consume(Token::Type::Arrow);

		const DataType return_type = consume_type();

		StatementPtr body = parse_compound_statement();

		const SourceRange source_range = {
			.start = function_range.start,
			.end = body->end_position(),
		};

		return std::make_unique<FunctionDeclaration>(
			source_range,
			identifier,
			std::move(arguments),
			return_type,
			std::move(body));
	}

	DeclarationPtr Parser::parse_translation_unit_declaration()
	{
		std::vector<DeclarationPtr> declarations = {};
		while (!match(Token::Type::Eof))
		{
			switch (current_token().type())
			{
			case Token::Type::Function:
				declarations.emplace_back(parse_function_declaration());
				break;
			case Token::Type::Import:
				// FIXME: Adding import declaration
				std::abort();
			default:
				m_diagnostics.error(
					current_token().source_range(),
					Diagnostics::ErrorCode::E0003,
					"declaration",
					current_token().type_string());
			}
		}

		const SourceRange source_range = {
			.start = declarations.front()->start_position(),
			.end = declarations.back()->end_position(),
		};

		return std::make_unique<TranslationUnitDeclaration>(
			source_range, m_file, std::move(declarations));
	}

	DeclarationPtr Parser::parse_variable_declaration()
	{
		const SourceRange let_range = consume(Token::Type::Let).source_range();

		const Token identifier_token = consume(Token::Type::Identifier);

		consume(Token::Type::Colon);

		const VariableDeclaration::MutableState mutable_state = [this]()
		{
			if (match(Token::Type::Mutable))
			{
				consume();
				return VariableDeclaration::MutableState::Yes;
			}

			return VariableDeclaration::MutableState::No;
		}();

		const DataType type = consume_type();

		ExpressionPtr expression = [this]() -> ExpressionPtr
		{
			if (match(Token::Type::Assign))
			{
				consume(Token::Type::Assign);
				return parse_binary_expression(0);
			}

			return nullptr;
		}();

		const Identifier identifier = {
			.value = identifier_token.value(),
			.source_range = identifier_token.source_range(),
		};

		const SourceRange source_range = {
			.start = let_range.start,
			.end = expression == nullptr ? type.end_position()
																	 : expression->end_position(),
		};

		return std::make_unique<VariableDeclaration>(
			source_range, identifier, mutable_state, type, std::move(expression));
	}

	ExpressionPtr Parser::parse_prefix_expression()
	{
		const Token &operation_token = current_token();

		const UnaryExpression::Operation::Kind kind = [&operation_token]()
		{
			switch (operation_token.type())
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

		if (kind == UnaryExpression::Operation::Kind::Invalid)
		{
			return parse_primary_expression();
		}

		consume();

		ExpressionPtr expression = parse_primary_expression();

		const UnaryExpression::Operation operation = {
			.kind = kind,
			.source_range = operation_token.source_range(),
		};

		const SourceRange source_range = {
			.start = operation_token.start_position(),
			.end = expression->end_position(),
		};

		return std::make_unique<UnaryExpression>(
			source_range, operation, std::move(expression));
	}

	ExpressionPtr Parser::parse_postfix_expression()
	{
		const Token identifier_token = consume(Token::Type::Identifier);
		if (match(Token::Type::RoundLeftBracket))
		{
			rewind_token();
			return parse_call_expression();
		}

		rewind_token();

		ExpressionPtr expression = parse_identifier_expression();

		const Token &operation_token = current_token();
		const UnaryExpression::Operation::Kind kind = [&operation_token]()
		{
			switch (operation_token.type())
			{
			case Token::Type::Increment:
				return UnaryExpression::Operation::Kind::PostIncrement;
			case Token::Type::Decrement:
				return UnaryExpression::Operation::Kind::PostDecrement;
			default:
				return UnaryExpression::Operation::Kind::Invalid;
			}
		}();

		if (kind == UnaryExpression::Operation::Kind::Invalid)
		{
			return expression;
		}

		consume();

		const UnaryExpression::Operation operation = {
			.kind = kind,
			.source_range = operation_token.source_range(),
		};

		const SourceRange source_range = {
			.start = identifier_token.start_position(),
			.end = expression->end_position(),
		};

		return std::make_unique<UnaryExpression>(
			source_range, operation, std::move(expression));
	}

	ExpressionPtr Parser::parse_paren_expression()
	{
		consume(Token::Type::RoundLeftBracket);

		ExpressionPtr expression = parse_binary_expression(0);

		consume(Token::Type::RoundRightBracket);

		return expression;
	}

	ExpressionPtr Parser::parse_primary_expression()
	{
		switch (current_token().type())
		{
		case Token::Type::Identifier:
			return parse_postfix_expression();
		case Token::Type::BoolLiteral:
			return parse_bool_literal();
		case Token::Type::FloatingLiteral:
			return parse_floating_literal();
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
		ExpressionPtr left = parse_prefix_expression();

		const Token token = [this, &left]()
		{
			if (current_token().type() != Token::Type::As)
			{
				return current_token();
			}

			consume();

			const DataType type = consume_type();

			const SourceRange source_range = {
				.start = left->start_position(),
				.end = type.end_position(),
			};

			left =
				std::make_unique<CastExpression>(source_range, std::move(left), type);

			return current_token();
		}();

		Token::Type token_type = token.type();

		if (match(Token::Type::Semicolon) || match(Token::Type::RoundRightBracket))
		{
			return left;
		}

		while (get_operator_precedence(token_type) > precedence)
		{
			consume();

			ExpressionPtr right =
				parse_binary_expression(get_operator_precedence(token_type));

			if (
				token_type == Token::Type::QuestionMark && match(Token::Type::Colon))
			{
				consume();

				ExpressionPtr temp =
					parse_binary_expression(get_operator_precedence(token_type));

				const SourceRange source_range = {
					.start = left->start_position(),
					.end = temp->end_position(),
				};

				return std::make_unique<ConditionalExpression>(
					source_range, std::move(left), std::move(right), std::move(temp));
			}

			const BinaryExpression::Operation::Kind kind = [this, token_type, &token]()
			{
				switch (token_type)
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
					m_diagnostics.error(
						token.source_range(),
						Diagnostics::ErrorCode::E0003,
						"operator",
						token.value());
				}
			}();

			const BinaryExpression::Operation operation = {
				.kind = kind,
				.source_range = token.source_range(),
			};

			const SourceRange source_range = {
				.start = left->start_position(),
				.end = right->end_position(),
			};

			left = std::make_unique<BinaryExpression>(
				source_range, operation, std::move(left), std::move(right));

			token_type = current_token().type();

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

		std::vector<ExpressionPtr> arguments = {};

		const SourceRange round_right_range =
			consume(Token::Type::RoundRightBracket).source_range();

		const Identifier identifier = {
			.value = identifier_token.value(),
			.source_range = identifier_token.source_range(),
		};

		const SourceRange source_range = {
			.start = identifier_token.start_position(),
			.end = round_right_range.end,
		};

		return std::make_unique<CallExpression>(
			source_range, identifier, std::move(arguments));
	}

	ExpressionPtr Parser::parse_identifier_expression()
	{
		const Token identifier_token = consume(Token::Type::Identifier);

		const Identifier identifier = {
			.value = identifier_token.value(),
			.source_range = identifier_token.source_range(),
		};

		return std::make_unique<IdentifierExpression>(
			identifier.source_range, identifier);
	}

	LiteralPtr Parser::parse_bool_literal()
	{
		const Token boolean = consume(Token::Type::BoolLiteral);
		return std::make_unique<BoolLiteral>(
			boolean.source_range(), boolean.value() == "true");
	}

	LiteralPtr Parser::parse_floating_literal()
	{
		const Token floating = consume(Token::Type::FloatingLiteral);
		return std::make_unique<FloatingLiteral>(
			floating.source_range(), floating.value());
	}

	LiteralPtr Parser::parse_integer_literal()
	{
		const Token integer = consume(Token::Type::IntegerLiteral);
		return std::make_unique<IntegerLiteral>(
			integer.source_range(), integer.value());
	}

	LiteralPtr Parser::parse_string_literal()
	{
		const Token string = consume(Token::Type::StringLiteral);
		return std::make_unique<StringLiteral>(
			string.source_range(), string.value());
	}

	StatementPtr Parser::parse_statement()
	{
		switch (current_token().type())
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
			rewind_token();
			return parse_expression_statement(parse_call_expression());
		}

		// TODO: Postfix can be changed to binary if binary returns null.
		if (match(Token::Type::Increment) || match(Token::Type::Decrement))
		{
			rewind_token();
			return parse_expression_statement(parse_postfix_expression());
		}

		switch (current_token().type())
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
			rewind_token();
			return parse_compound_assign_statement();
		default:
			break;
		}

		consume(Token::Type::Assign);

		ExpressionPtr expression = parse_binary_expression(0);

		const Identifier identifier = {
			.value = identifier_token.value(),
			.source_range = identifier_token.source_range(),
		};

		const SourceRange source_range = {
			.start = identifier_token.start_position(),
			.end = expression->end_position(),
		};

		return std::make_unique<AssignStatement>(
			source_range, identifier, std::move(expression));
	}

	StatementPtr Parser::parse_compound_statement()
	{
		const SourceRange curly_left_range =
			consume(Token::Type::CurlyLeftBracket).source_range();

		std::vector<StatementPtr> statements = {};
		while (!match(Token::Type::CurlyRightBracket))
		{
			StatementPtr statement = parse_statement();
			if (statement == nullptr)
			{
				break;
			}

			switch (statement->class_category())
			{
			case AstNode::Category::AssignStatement:
			case AstNode::Category::CompoundAssignStatement:
			case AstNode::Category::ExpressionStatement:
			case AstNode::Category::ReturnStatement:
			case AstNode::Category::VariableDeclaration:
				consume(Token::Type::Semicolon);
				break;
			default:
				break;
			}

			statements.emplace_back(std::move(statement));
		}

		const SourceRange curly_right_range =
			consume(Token::Type::CurlyRightBracket).source_range();

		const SourceRange source_range = {
			.start = curly_left_range.start,
			.end = curly_right_range.end,
		};

		return std::make_unique<CompoundStatement>(
			source_range, std::move(statements));
	}

	StatementPtr Parser::parse_compound_assign_statement()
	{
		const Token identifier_token = consume(Token::Type::Identifier);

		const CompoundAssignStatement::Operation operation = [this]()
		{
			switch (current_token().type())
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

		ExpressionPtr expression = parse_binary_expression(0);

		const Identifier identifier = {
			.value = identifier_token.value(),
			.source_range = identifier_token.source_range(),
		};

		const SourceRange source_range = {
			.start = identifier_token.start_position(),
			.end = expression->end_position(),
		};

		return std::make_unique<CompoundAssignStatement>(
			source_range, identifier, operation, std::move(expression));
	}

	StatementPtr Parser::parse_expression_statement(ExpressionPtr expression)
	{
		return std::make_unique<ExpressionStatement>(
			expression->source_range(), std::move(expression));
	}

	StatementPtr Parser::parse_if_statement()
	{
		const SourceRange if_range = consume(Token::Type::If).source_range();

		consume(Token::Type::RoundLeftBracket);

		ExpressionPtr condition = parse_binary_expression(0);

		consume(Token::Type::RoundRightBracket);

		StatementPtr true_body = parse_compound_statement();

		StatementPtr false_body = [this]() -> StatementPtr
		{
			if (match(Token::Type::Else))
			{
				consume();
				return parse_compound_statement();
			}

			return nullptr;
		}();

		const SourceRange source_range = {
			.start = if_range.start,
			.end = false_body == nullptr ? true_body->end_position()
																	 : false_body->end_position(),
		};

		return std::make_unique<IfStatement>(
			source_range,
			std::move(condition),
			std::move(true_body),
			std::move(false_body));
	}

	StatementPtr Parser::parse_return_statement()
	{
		const SourceRange return_range =
			consume(Token::Type::Return).source_range();

		if (match(Token::Type::Semicolon))
		{
			return std::make_unique<ReturnStatement>(return_range, nullptr);
		}

		ExpressionPtr expression = parse_binary_expression(0);

		const SourceRange source_range = {
			.start = return_range.start,
			.end = expression->end_position(),
		};

		return std::make_unique<ReturnStatement>(
			source_range, std::move(expression));
	}

	StatementPtr Parser::parse_while_statement()
	{
		const SourceRange while_range = consume(Token::Type::While).source_range();

		consume(Token::Type::RoundLeftBracket);

		ExpressionPtr condition = parse_binary_expression(0);

		consume(Token::Type::RoundRightBracket);

		StatementPtr body = parse_compound_statement();

		const SourceRange source_range = {
			.start = while_range.start,
			.end = body->end_position(),
		};

		return std::make_unique<WhileStatement>(
			source_range, std::move(condition), std::move(body));
	}

	Token Parser::last_token() const noexcept
	{
		if (m_token_index == 0)
		{
			return {};
		}

		return m_tokens[m_token_index - 1];
	}

	Token Parser::current_token() const noexcept
	{
		if (m_token_index >= m_tokens.size())
		{
			return {};
		}

		return m_tokens[m_token_index];
	}

	Token Parser::peek_token() const noexcept
	{
		if (m_token_index + 1 >= m_tokens.size())
		{
			return {};
		}

		return m_tokens[m_token_index + 1];
	}

	void Parser::rewind_token() noexcept
	{
		if (m_token_index == 0)
		{
			return;
		}

		--m_token_index;
	}

	bool Parser::match(Token::Type token_type) const noexcept
	{
		return current_token().type() == token_type;
	}

	Token Parser::consume() noexcept
	{
		if (m_token_index < m_tokens.size())
		{
			++m_token_index;
		}

		return last_token();
	}

	Token Parser::consume(Token::Type token_type) noexcept
	{
		if (!match(token_type))
		{
			const Token &token = current_token();

			const Position position = [&]()
			{
				if (token_type == Token::Type::Semicolon)
				{
					return last_token().start_position();
				}

				return token.start_position();
			}();

			const SourceRange source_range = {
				.start = position,
				.end = token.end_position(),
			};

			m_diagnostics.error(
				source_range,
				Diagnostics::ErrorCode::E0003,
				Token::token_type_to_string(token_type),
				token.value());
		}

		return consume();
	}

	DataType Parser::consume_type()
	{
		const Token token = current_token();
		const DataType data_type = token.data_type();
		if (data_type.kind() == DataType::Kind::Invalid)
		{
			m_diagnostics.error(
				token.source_range(),
				Diagnostics::ErrorCode::E0003,
				"type",
				token.value());
		}

		consume();

		return data_type;
	}

	Identifier Parser::consume_identifier()
	{
		const Token token = current_token();
		if (!match(Token::Type::Identifier))
		{
			m_diagnostics.error(
				token.source_range(),
				Diagnostics::ErrorCode::E0003,
				"identifier",
				token.value());
		}

		consume();

		const Identifier identifier = {
			.value = token.value(),
			.source_range = token.source_range(),
		};

		return identifier;
	}

	uint8_t Parser::get_operator_precedence(Token::Type token_type) const noexcept
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
			return 0;
		}
	}
} // namespace hyper
