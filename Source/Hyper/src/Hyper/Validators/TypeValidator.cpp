/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Validators/TypeValidator.hpp"

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

namespace Hyper
{
	TypeValidator::TypeValidator(
		Diagnostics &diagnostics,
		AstPtr &ast,
		std::vector<Symbol> symbols)
		: Validator(diagnostics, ast)
		, m_symbols(std::move(symbols))
	{
	}

	void TypeValidator::accept(FunctionDeclaration &declaration)
	{
		m_current_function = find_symbol(declaration.identifier().value);
		declaration.body()->validate(*this);
		m_current_function = {};
	}

	void TypeValidator::accept(TranslationUnitDeclaration &declaration)
	{
		for (const auto &translation_unit_declaration : declaration.declarations())
		{
			translation_unit_declaration->validate(*this);
		}
	}

	void TypeValidator::accept(VariableDeclaration &declaration)
	{
		if (declaration.expression() == nullptr)
		{
			return;
		}

		declaration.expression()->validate(*this);
		if (declaration.type().kind != m_current_type.kind)
		{
		}
	}

	void TypeValidator::accept(BinaryExpression &expression)
	{
		(void) expression;
		expression.left()->validate(*this);
		expression.right()->validate(*this);
	}

	void TypeValidator::accept(CallExpression &)
	{
		// TODO: Validate arguments
	}

	void TypeValidator::accept(CastExpression &expression)
	{
		expression.expression()->validate(*this);
		m_current_type = expression.type();
	}

	void TypeValidator::accept(ConditionalExpression &expression)
	{
		(void) expression;
		expression.condition()->validate(*this);
		expression.true_expression()->validate(*this);
		expression.false_expression()->validate(*this);
	}

	void TypeValidator::accept(IdentifierExpression &expression)
	{
		const Symbol symbol = find_symbol(expression.identifier().value);
		m_current_type = symbol.type;
	}

	void TypeValidator::accept(UnaryExpression &expression)
	{
		(void) expression;
		expression.expression()->validate(*this);
	}

	void TypeValidator::accept(BoolLiteral &literal)
	{
		const Type type = {
			.value = "bool",
			.kind = Type::Kind::Bool,
			.range = literal.range(),
		};

		m_current_type = type;
	}

	void TypeValidator::accept(IntegerLiteral &literal)
	{
		const Type type = {
			.value = "i32",
			.kind = Type::Kind::Int32,
			.range = literal.range(),
		};

		m_current_type = type;
	}

	void TypeValidator::accept(StringLiteral &literal)
	{
		const Type type = {
			.value = "string",
			.kind = Type::Kind::String,
			.range = literal.range(),
		};

		m_current_type = type;
	}

	void TypeValidator::accept(AssignStatement &statement)
	{
		statement.expression()->validate(*this);

		const Symbol symbol = find_symbol(statement.identifier().value);
		if (symbol.type.kind != m_current_type.kind)
		{
			const std::string error = Formatter::format(
				"assigning to '{}' from incompatible type '{}'",
				symbol.type.value,
				m_current_type.value);
			const SourceRange range = {
				.start = symbol.type.range.start,
				.end = statement.expression()->range().end,
			};
			m_diagnostics.error(range, error);
		}
	}

	void TypeValidator::accept(CompoundAssignStatement &statement)
	{
		statement.expression()->validate(*this);

		const Symbol symbol = find_symbol(statement.identifier().value);
		if (symbol.type.kind != m_current_type.kind)
		{
			const std::string error = Formatter::format(
				"assigning to '{}' from incompatible type '{}'",
				symbol.type.value,
				m_current_type.value);
			const SourceRange range = {
				.start = symbol.type.range.start,
				.end = statement.expression()->range().end,
			};
			m_diagnostics.error(range, error);
		}
	}

	void TypeValidator::accept(CompoundStatement &statement)
	{
		for (const auto &compound_statement : statement.statements())
		{
			compound_statement->validate(*this);
		}
	}

	void TypeValidator::accept(ExpressionStatement &statement)
	{
		statement.expression()->validate(*this);
	}

	void TypeValidator::accept(IfStatement &statement)
	{
		statement.condition()->validate(*this);
		statement.true_body()->validate(*this);

		if (statement.false_body() != nullptr)
		{
			statement.false_body()->validate(*this);
		}
	}

	void TypeValidator::accept(ReturnStatement &statement)
	{
		statement.expression()->validate(*this);

		if (m_current_function.type.kind != m_current_type.kind)
		{
			const std::string error = Formatter::format(
				"returning '{}' from a function with incompatible result type '{}'",
				m_current_type.value,
				m_current_function.type.value);
			const SourceRange range = {
				.start = m_current_function.type.range.start,
				.end = statement.expression()->range().end,
			};
			m_diagnostics.error(range, error);
		}
	}

	void TypeValidator::accept(WhileStatement &statement)
	{
		statement.condition()->validate(*this);
		statement.body()->validate(*this);
	}

	Symbol TypeValidator::find_symbol(const std::string &identifier) const
	{
		for (const Symbol &symbol : m_symbols)
		{
			if (symbol.identifier != identifier)
			{
				continue;
			}

			return symbol;
		}

		return {};
	}
} // namespace Hyper
