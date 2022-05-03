/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/parser.hpp"

#include "hyper/ast/ast.hpp"
#include "hyper/lexer.hpp"
#include "hyper_utilities/assertions.hpp"
#include "hyper_utilities/profiler.hpp"
#include "hyper_utilities/platform_detection.hpp"

namespace hyper
{
	Parser::Parser(
		const Diagnostics &diagnostics,
		const std::vector<Token> &tokens,
		std::string_view file)
		: m_diagnostics(diagnostics)
		, m_tokens(tokens)
		, m_file(file)
	{
	}

	AstNode *Parser::parse()
	{
		HYPER_PROFILE_FUNCTION();

		return parse_translation_unit_declaration();
	}

	Declaration *Parser::parse_declaration()
	{
		HYPER_PROFILE_FUNCTION();

		switch (current_token().type())
		{
		case Token::Type::Extern:
			return parse_extern_declaration();
		case Token::Type::Function:
			return parse_function_declaration();
		case Token::Type::Import:
			return parse_import_declaration();
		case Token::Type::Module:
			return parse_module_declaration();
		case Token::Type::Public:
			return parse_public_declaration();
		case Token::Type::Static:
			return parse_static_declaration();
		case Token::Type::Struct:
			return parse_struct_declaration();
		case Token::Type::SquareLeftBracket:
			return parse_attribute_declaration();
		default:
			return nullptr;
		}
	}

	Declaration *Parser::parse_attribute_declaration()
	{
		HYPER_PROFILE_FUNCTION();

		const SourceRange square_left_range =
			consume(Token::Type::SquareLeftBracket).source_range();

		// TODO:

		const std::string attribute = consume(Token::Type::Identifier).value();

		consume(Token::Type::Assign);

		const std::string value = consume(Token::Type::StringLiteral).value();

		const SourceRange square_right_range =
			consume(Token::Type::SquareRightBracket).source_range();

		const SourceRange source_range = {
			.start = square_left_range.start,
			.end = square_right_range.end,
		};

		return new AttributeDeclaration(
			source_range, attribute, value.substr(1, value.length() - 2));
	}

	Declaration *Parser::parse_extern_declaration()
	{
		HYPER_PROFILE_FUNCTION();

		const SourceRange extern_range =
			consume(Token::Type::Extern).source_range();

		// TODO:

		if (match(Token::Type::RoundLeftBracket))
		{
			consume();
			consume(Token::Type::Identifier);
			consume(Token::Type::RoundRightBracket);
		}

		if (!match(Token::Type::Function))
		{
			Statement *statement = parse_statement();
			m_diagnostics.error(
				statement->source_range(),
				Diagnostics::ErrorCode::E0008,
				statement->class_name());
		}

		Statement *statement = parse_function_declaration();

		const SourceRange source_range = {
			.start = extern_range.start,
			.end = statement->end_position(),
		};

		return new ExternDeclaration(source_range, statement);
	}

	Declaration *Parser::parse_field_declaration()
	{
		HYPER_PROFILE_FUNCTION();

		const Token identifier_token = consume(Token::Type::Identifier);

		consume(Token::Type::Colon);

		// TODO:

		const DataType type = consume_type();

		Expression *expression = [this]() -> Expression *
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
			.start = identifier.source_range.start,
			.end = expression == nullptr ? type.end_position()
																	 : expression->end_position(),
		};

		return new FieldDeclaration(
			source_range, type, identifier, std::move(expression));
	}

	Declaration *Parser::parse_function_declaration()
	{
		HYPER_PROFILE_FUNCTION();

		const SourceRange function_range =
			consume(Token::Type::Function).source_range();
		const Identifier identifier = consume_identifier();

		consume(Token::Type::RoundLeftBracket);

		std::vector<Declaration *> arguments = {};
		while (!match(Token::Type::RoundRightBracket))
		{
			Declaration *parameter_declaration = parse_parameter_declaration();
			arguments.emplace_back(parameter_declaration);
			if (match(Token::Type::Comma))
			{
				consume();
			}
		}

		consume(Token::Type::RoundRightBracket);
		consume(Token::Type::Arrow);

		const DataType return_type = consume_type();

		Statement *body = nullptr;
		if (match(Token::Type::Semicolon))
		{
			consume();
		}
		else
		{
			body = parse_compound_statement();
		}

		const SourceRange source_range = {
			.start = function_range.start,
			.end =
				body == nullptr ? return_type.end_position() : body->end_position(),
		};

		return new FunctionDeclaration(
			source_range,
			identifier,
			std::move(arguments),
			return_type,
			std::move(body));
	}

	Declaration *Parser::parse_import_declaration()
	{
		HYPER_PROFILE_FUNCTION();

		const SourceRange import_range =
			consume(Token::Type::Import).source_range();

		Position module_start_position = {};
		Position module_end_position = {};
		std::string module_name;
		while (!match(Token::Type::Semicolon))
		{
			const Token token = consume(Token::Type::Identifier);
			if (module_start_position.line == 0)
			{
				module_start_position = token.start_position();
			}

			module_end_position = token.end_position();

			module_name += token.value();

			if (
				match(Token::Type::Colon) && peek_token().type() == Token::Type::Colon)
			{
				consume();
				consume();
				module_name += "::";
			}
		}

		// TODO:

#if HYPER_PLATFORM_WINDOWS
		const std::string slash = "\\";
#elif HYPER_PLATFORM_LINUX
		const std::string slash = "/";
#endif

		std::string file_name;
		std::string path;

		size_t dot_position = module_name.find_last_of("::");
		if (dot_position == std::string::npos)
		{
			file_name = module_name;
			path = "";
		}
		else
		{
			file_name = module_name.substr(dot_position + 1);
			path = module_name.substr(0, dot_position);
		}

		file_name += ".hyper";
		utilities::replace_string(path, "::", slash);
		const std::string file = path + slash + file_name;

		const Position end_position =
			consume(Token::Type::Semicolon).end_position();

		const Identifier identifier = {
			.value = module_name,
			.source_range = {
				.start = module_start_position,
				.end = module_end_position,
			},
		};

		const SourceRange source_range = {
			.start = import_range.start,
			.end = end_position,
		};

		return new ImportDeclaration(source_range, identifier, file);
	}

	Declaration *Parser::parse_module_declaration()
	{
		HYPER_PROFILE_FUNCTION();

		const SourceRange module_range =
			consume(Token::Type::Module).source_range();

		Position module_start_position = {};
		Position module_end_position = {};
		std::string module_name;
		while (!match(Token::Type::CurlyLeftBracket))
		{
			const Token token = consume(Token::Type::Identifier);
			if (module_start_position.line == 0)
			{
				module_start_position = token.start_position();
			}

			module_end_position = token.end_position();

			module_name += token.value();

			if (
				match(Token::Type::Colon) && peek_token().type() == Token::Type::Colon)
			{
				consume();
				consume();
				module_name += "::";
			}
		}

		consume(Token::Type::CurlyLeftBracket);

		std::vector<Declaration *> declarations = {};
		while (true)
		{
			Declaration *declaration = parse_declaration();
			if (declaration == nullptr)
			{
				break;
			}

			declarations.emplace_back(declaration);
		}

		const Position end_position =
			consume(Token::Type::CurlyRightBracket).end_position();

		const Identifier identifier = {
			.value = module_name,
			.source_range = {
				.start = module_start_position,
				.end = module_end_position,
			},
		};

		const SourceRange source_range = {
			.start = module_range.start,
			.end = end_position,
		};

		return new ModuleDeclaration(source_range, identifier, declarations);
	} // namespace hyper

	Declaration *Parser::parse_parameter_declaration()
	{
		HYPER_PROFILE_FUNCTION();

		const Token identifier_token = consume(Token::Type::Identifier);

		consume(Token::Type::Colon);

		const ParameterDeclaration::MutableState mutable_state = [this]()
		{
			if (match(Token::Type::Mutable))
			{
				consume();
				return ParameterDeclaration::MutableState::Yes;
			}

			return ParameterDeclaration::MutableState::No;
		}();

		const DataType type = consume_type();

		const Identifier identifier = {
			.value = identifier_token.value(),
			.source_range = identifier_token.source_range(),
		};

		const SourceRange source_range = {
			.start = identifier_token.start_position(),
			.end = type.end_position(),
		};

		return new ParameterDeclaration(
			source_range, identifier, mutable_state, type);
	}

	Declaration *Parser::parse_public_declaration()
	{
		HYPER_PROFILE_FUNCTION();

		const SourceRange public_range =
			consume(Token::Type::Public).source_range();

		const bool is_function = match(Token::Type::Function);
		const bool is_struct = match(Token::Type::Struct);
		const bool is_static = match(Token::Type::Static);
		const bool is_field = match(Token::Type::Identifier);
		if (!is_function && !is_struct && !is_static && !is_field)
		{
			Statement *statement = parse_statement();
			m_diagnostics.error(
				statement->source_range(),
				Diagnostics::ErrorCode::E0007,
				statement->class_name());
		}

		Statement *statement = nullptr;
		if (is_function)
		{
			statement = parse_function_declaration();
		}
		else if (is_struct)
		{
			statement = parse_struct_declaration();
		}
		else if (is_static)
		{
			statement = parse_static_declaration();
		}
		else if (is_field)
		{
			statement = parse_field_declaration();
		}

		const SourceRange source_range = {
			.start = public_range.start,
			.end = statement->end_position(),
		};

		return new PublicDeclaration(source_range, statement);
	}

	Declaration *Parser::parse_static_declaration()
	{
		HYPER_PROFILE_FUNCTION();

		const SourceRange static_range =
			consume(Token::Type::Static).source_range();

		// TODO:

		if (!match(Token::Type::Identifier))
		{
			Statement *statement = parse_statement();
			m_diagnostics.error(
				statement->source_range(),
				Diagnostics::ErrorCode::E0007,
				statement->class_name());
		}

		Declaration *declaration = parse_field_declaration();

		const SourceRange source_range = {
			.start = static_range.start,
			.end = declaration->end_position(),
		};

		return new StaticDeclaration(source_range, declaration);
	}

	Declaration *Parser::parse_struct_declaration()
	{
		HYPER_PROFILE_FUNCTION();

		const SourceRange struct_range =
			consume(Token::Type::Struct).source_range();

		const Token identifier_token = consume(Token::Type::Identifier);

		consume(Token::Type::CurlyLeftBracket);

		std::vector<Declaration *> declarations = {};
		while (!match(Token::Type::CurlyRightBracket))
		{
			Declaration *declaration = [&]() -> Declaration *
			{
				switch (current_token().type())
				{
				case Token::Type::Public:
					return parse_public_declaration();
				case Token::Type::Static:
					return parse_static_declaration();
				case Token::Type::Identifier:
					return parse_field_declaration();
				default:
					return nullptr;
				}
			}();

			if (declaration == nullptr)
			{
				// TODO:
				return nullptr;
			}

			consume(Token::Type::Semicolon);

			declarations.emplace_back(std::move(declaration));
		}

		const SourceRange curly_right_range =
			consume(Token::Type::CurlyRightBracket).source_range();

		const Identifier identifier = {
			.value = identifier_token.value(),
			.source_range = identifier_token.source_range(),
		};

		const SourceRange source_range = {
			.start = struct_range.start,
			.end = curly_right_range.end,
		};

		return new StructDeclaration(source_range, identifier, declarations);
	}

	Declaration *Parser::parse_translation_unit_declaration()
	{
		HYPER_PROFILE_FUNCTION();

		std::vector<Declaration *> declarations = {};
		while (!match(Token::Type::Eof))
		{
			Declaration *declaration = parse_declaration();
			if (declaration == nullptr)
			{
				m_diagnostics.error(
					current_token().source_range(),
					Diagnostics::ErrorCode::E0003,
					"declaration",
					current_token().type_string());
			}

			declarations.emplace_back(declaration);
		}

		const SourceRange source_range = {
			.start = declarations.front()->start_position(),
			.end = declarations.back()->end_position(),
		};

		return new TranslationUnitDeclaration(
			source_range, std::string(m_file), std::move(declarations));
	}

	Declaration *Parser::parse_variable_declaration()
	{
		HYPER_PROFILE_FUNCTION();

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

		Expression *expression = [this]() -> Expression *
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

		return new VariableDeclaration(
			source_range, identifier, mutable_state, type, std::move(expression));
	}

	Expression *Parser::parse_binary_expression(uint8_t precedence)
	{
		HYPER_PROFILE_FUNCTION();

		Expression *left = parse_prefix_expression();

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

			left = new CastExpression(source_range, std::move(left), type);

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

			Expression *right =
				parse_binary_expression(get_operator_precedence(token_type));

			if (token_type == Token::Type::QuestionMark && match(Token::Type::Colon))
			{
				consume();

				Expression *temp =
					parse_binary_expression(get_operator_precedence(token_type));

				const SourceRange source_range = {
					.start = left->start_position(),
					.end = temp->end_position(),
				};

				return new ConditionalExpression(
					source_range, std::move(left), std::move(right), std::move(temp));
			}

			const BinaryExpression::Operation::Kind kind =
				[this, token_type, &token]()
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

			left = new BinaryExpression(
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

	Expression *Parser::parse_call_expression()
	{
		HYPER_PROFILE_FUNCTION();

		const Identifier identifier = consume_identifier();

		consume(Token::Type::RoundLeftBracket);

		std::vector<Expression *> arguments = {};
		while (!match(Token::Type::RoundRightBracket))
		{
			Expression *expression = parse_binary_expression(0);
			arguments.emplace_back(expression);

			if (match(Token::Type::Comma))
			{
				consume();
			}
		}

		const SourceRange round_right_range =
			consume(Token::Type::RoundRightBracket).source_range();

		const SourceRange source_range = {
			.start = identifier.source_range.start,
			.end = round_right_range.end,
		};

		return new CallExpression(source_range, identifier, std::move(arguments));
	}

	Expression *Parser::parse_identifier_expression()
	{
		HYPER_PROFILE_FUNCTION();

		const Identifier identifier = consume_identifier();
		return new IdentifierExpression(identifier.source_range, identifier);
	}

	Expression *Parser::parse_initializer_list_expression()
	{
		HYPER_PROFILE_FUNCTION();

		// TODO:

		const SourceRange left_curly_range =
			consume(Token::Type::CurlyLeftBracket).source_range();

		std::vector<Expression *> expressions = {};
		while (!match(Token::Type::CurlyRightBracket))
		{
			if (!match(Token::Type::Dot))
			{
				Expression *expression = parse_binary_expression(0);
				expressions.push_back(expression);
			}
			else
			{
				consume();
				consume(Token::Type::Identifier);
				consume(Token::Type::Assign);

				Expression *expression = [&]()
				{
					if (match(Token::Type::CurlyLeftBracket))
					{
						return parse_initializer_list_expression();
					}

					return parse_binary_expression(0);
				}();

				expressions.push_back(expression);
			}

			if (match(Token::Type::Comma))
			{
				consume();
			}
		}

		const SourceRange right_curly_range =
			consume(Token::Type::CurlyRightBracket).source_range();

		const SourceRange source_range = {
			.start = left_curly_range.start,
			.end = right_curly_range.end,
		};

		return new InitializerListExpression(source_range, expressions);
	}

	Expression *Parser::parse_member_expression()
	{
		HYPER_PROFILE_FUNCTION();

		const Identifier struct_identifier = consume_identifier();

		const bool is_arrow = match(Token::Type::Arrow);
		consume();

		const Identifier member_identifier = consume_identifier();

		const SourceRange source_range = {
			.start = struct_identifier.source_range.start,
			.end = member_identifier.source_range.end,
		};

		return new MemberExpression(
			source_range, struct_identifier, is_arrow, member_identifier);
	}

	Expression *Parser::parse_paren_expression()
	{
		HYPER_PROFILE_FUNCTION();

		consume(Token::Type::RoundLeftBracket);

		Expression *expression = parse_binary_expression(0);

		consume(Token::Type::RoundRightBracket);

		return expression;
	}

	Expression *Parser::parse_postfix_expression()
	{
		HYPER_PROFILE_FUNCTION();

		const Identifier identifier = consume_identifier();
		if (match(Token::Type::RoundLeftBracket))
		{
			for (size_t i = 0; i < identifier.count; ++i)
			{
				rewind_token();
			}
			return parse_call_expression();
		}

		if (match(Token::Type::Dot) || match(Token::Type::Arrow))
		{
			for (size_t i = 0; i < identifier.count; ++i)
			{
				rewind_token();
			}
			return parse_member_expression();
		}

		for (size_t i = 0; i < identifier.count; ++i)
		{
			rewind_token();
		}

		Expression *expression = parse_identifier_expression();

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
			.start = identifier.source_range.start,
			.end = expression->end_position(),
		};

		return new UnaryExpression(source_range, operation, std::move(expression));
	}

	Expression *Parser::parse_prefix_expression()
	{
		HYPER_PROFILE_FUNCTION();

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
			case Token::Type::BitwiseAnd:
				return UnaryExpression::Operation::Kind::AddressOf;
			case Token::Type::Star:
				return UnaryExpression::Operation::Kind::Dereference;
			default:
				return UnaryExpression::Operation::Kind::Invalid;
			}
		}();

		if (kind == UnaryExpression::Operation::Kind::Invalid)
		{
			return parse_primary_expression();
		}

		consume();

		Expression *expression = parse_primary_expression();

		const UnaryExpression::Operation operation = {
			.kind = kind,
			.source_range = operation_token.source_range(),
		};

		const SourceRange source_range = {
			.start = operation_token.start_position(),
			.end = expression->end_position(),
		};

		return new UnaryExpression(source_range, operation, std::move(expression));
	}

	Expression *Parser::parse_primary_expression()
	{
		HYPER_PROFILE_FUNCTION();

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
		case Token::Type::CurlyLeftBracket:
			return parse_initializer_list_expression();
		default:
			break;
		}

		return nullptr;
	}

	Literal *Parser::parse_bool_literal()
	{
		HYPER_PROFILE_FUNCTION();

		const Token boolean = consume(Token::Type::BoolLiteral);
		return new BoolLiteral(boolean.source_range(), boolean.value() == "true");
	}

	Literal *Parser::parse_floating_literal()
	{
		HYPER_PROFILE_FUNCTION();

		const Token floating = consume(Token::Type::FloatingLiteral);
		return new FloatingLiteral(floating.source_range(), floating.value());
	}

	Literal *Parser::parse_integer_literal()
	{
		HYPER_PROFILE_FUNCTION();

		const Token integer = consume(Token::Type::IntegerLiteral);
		return new IntegerLiteral(integer.source_range(), integer.value());
	}

	Literal *Parser::parse_string_literal()
	{
		HYPER_PROFILE_FUNCTION();

		const Token string = consume(Token::Type::StringLiteral);
		return new StringLiteral(string.source_range(), string.value());
	}

	Statement *Parser::parse_statement()
	{
		HYPER_PROFILE_FUNCTION();

		switch (current_token().type())
		{
		case Token::Type::Increment:
		case Token::Type::Decrement:
			return parse_expression_statement(parse_prefix_expression());
		case Token::Type::BoolLiteral:
		case Token::Type::FloatingLiteral:
		case Token::Type::IntegerLiteral:
		case Token::Type::StringLiteral:
			return parse_expression_statement(parse_binary_expression(0));
		case Token::Type::Identifier:
			return parse_assign_statement();
		case Token::Type::If:
			return parse_if_statement();
		case Token::Type::Print:
			return parse_print_statement();
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

	Statement *Parser::parse_assign_statement()
	{
		HYPER_PROFILE_FUNCTION();

		const Identifier identifier = consume_identifier();
		if (match(Token::Type::RoundLeftBracket))
		{
			for (size_t i = 0; i < identifier.count; ++i)
			{
				rewind_token();
			}
			return parse_expression_statement(parse_call_expression());
		}

		// TODO:
		if (match(Token::Type::Increment) || match(Token::Type::Decrement))
		{
			for (size_t i = 0; i < identifier.count; ++i)
			{
				rewind_token();
			}
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

		Expression *expression = parse_binary_expression(0);

		const SourceRange source_range = {
			.start = identifier.source_range.start,
			.end = expression->end_position(),
		};

		return new AssignStatement(source_range, identifier, std::move(expression));
	}

	Statement *Parser::parse_compound_statement()
	{
		HYPER_PROFILE_FUNCTION();

		const SourceRange curly_left_range =
			consume(Token::Type::CurlyLeftBracket).source_range();

		std::vector<Statement *> statements = {};
		while (!match(Token::Type::CurlyRightBracket))
		{
			Statement *statement = parse_statement();
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
			case AstNode::Category::PrintStatement:
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

		return new CompoundStatement(source_range, std::move(statements));
	}

	Statement *Parser::parse_compound_assign_statement()
	{
		HYPER_PROFILE_FUNCTION();

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

		Expression *expression = parse_binary_expression(0);

		const Identifier identifier = {
			.value = identifier_token.value(),
			.source_range = identifier_token.source_range(),
		};

		const SourceRange source_range = {
			.start = identifier_token.start_position(),
			.end = expression->end_position(),
		};

		return new CompoundAssignStatement(
			source_range, identifier, operation, std::move(expression));
	}

	Statement *Parser::parse_expression_statement(Expression *expression)
	{
		HYPER_PROFILE_FUNCTION();

		return new ExpressionStatement(
			expression->source_range(), std::move(expression));
	}

	Statement *Parser::parse_if_statement()
	{
		HYPER_PROFILE_FUNCTION();

		const SourceRange if_range = consume(Token::Type::If).source_range();

		consume(Token::Type::RoundLeftBracket);

		Expression *condition = parse_binary_expression(0);

		consume(Token::Type::RoundRightBracket);

		Statement *true_body = parse_compound_statement();

		Statement *false_body = [this]() -> Statement *
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

		return new IfStatement(
			source_range,
			std::move(condition),
			std::move(true_body),
			std::move(false_body));
	}

	Statement *Parser::parse_print_statement()
	{
		HYPER_PROFILE_FUNCTION();

		const SourceRange print_range = consume(Token::Type::Print).source_range();

		consume(Token::Type::RoundLeftBracket);

		Expression *expression = parse_binary_expression(0);

		consume(Token::Type::RoundRightBracket);

		const SourceRange source_range = {
			.start = print_range.start,
			.end = expression->end_position(),
		};

		return new PrintStatement(source_range, std::move(expression));
	}

	Statement *Parser::parse_return_statement()
	{
		HYPER_PROFILE_FUNCTION();

		const SourceRange return_range =
			consume(Token::Type::Return).source_range();

		if (match(Token::Type::Semicolon))
		{
			return new ReturnStatement(return_range, nullptr);
		}

		Expression *expression = parse_binary_expression(0);

		const SourceRange source_range = {
			.start = return_range.start,
			.end = expression->end_position(),
		};

		return new ReturnStatement(source_range, std::move(expression));
	}

	Statement *Parser::parse_while_statement()
	{
		HYPER_PROFILE_FUNCTION();

		const SourceRange while_range = consume(Token::Type::While).source_range();

		consume(Token::Type::RoundLeftBracket);

		Expression *condition = parse_binary_expression(0);

		consume(Token::Type::RoundRightBracket);

		Statement *body = parse_compound_statement();

		const SourceRange source_range = {
			.start = while_range.start,
			.end = body->end_position(),
		};

		return new WhileStatement(
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
		HYPER_PROFILE_FUNCTION();

		if (m_token_index < m_tokens.size())
		{
			++m_token_index;
		}

		return last_token();
	}

	Token Parser::consume(Token::Type token_type) noexcept
	{
		HYPER_PROFILE_FUNCTION();

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
		HYPER_PROFILE_FUNCTION();

		std::string value;
		DataType::Kind kind = DataType::Kind::Invalid;
		Position start_position = {};
		Position end_position = {};
		while (true)
		{
			const Token token = current_token();
			const DataType data_type = token.data_type();

			if (data_type.kind() == DataType::Kind::Invalid)
			{
				if (value.empty())
				{
					m_diagnostics.error(
						token.source_range(),
						Diagnostics::ErrorCode::E0003,
						"type",
						token.value());
				}

				break;
			}

			value += token.value();

			if (kind == DataType::Kind::Invalid)
			{
				kind = data_type.kind();
			}

			// TODO:
			if (start_position.line == 0)
			{
				start_position = token.start_position();
			}

			end_position = token.end_position();

			consume();

			if (
				match(Token::Type::Colon) && peek_token().type() == Token::Type::Colon)
			{
				consume();
				consume();
				value += "::";
			}
		}

		bool array = false;
		if (match(Token::Type::SquareLeftBracket))
		{
			consume();
			array = true;

			if (match(Token::Type::IntegerLiteral))
			{
				consume();
				// TODO:
			}

			consume(Token::Type::SquareRightBracket);
		}

		bool pointer = false;
		if (match(Token::Type::Star))
		{
			consume();
			pointer = true;
		}

		const SourceRange source_range = {
			.start = start_position,
			.end = end_position,
		};

		return DataType(value, kind, array, pointer, source_range);
	}

	Identifier Parser::consume_identifier()
	{
		HYPER_PROFILE_FUNCTION();

		std::string value;
		Position start_position = {};
		Position end_position = {};
		size_t count = 0;
		while (match(Token::Type::Identifier))
		{
			const Token token = current_token();
			const DataType data_type = token.data_type();

			if (data_type.kind() != DataType::Kind::UserDefined)
			{
				m_diagnostics.error(
					token.source_range(),
					Diagnostics::ErrorCode::E0003,
					"identifier",
					token.value());
			}

			value += token.value();

			// TODO:
			if (start_position.line == 0)
			{
				start_position = token.start_position();
			}

			end_position = token.end_position();

			consume();
			++count;

			if (
				match(Token::Type::Colon) && peek_token().type() == Token::Type::Colon)
			{
				consume();
				consume();
				count += 2;
				value += "::";
			}
		}

		const SourceRange source_range = {
			.start = start_position,
			.end = end_position,
		};

		const Identifier identifier = {
			.value = value,
			.source_range = source_range,
			.count = count,
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
