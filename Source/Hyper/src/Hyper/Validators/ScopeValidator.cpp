/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Validators/ScopeValidator.hpp"

#include "Hyper/Ast/Declarations/FunctionDeclaration.hpp"
#include "Hyper/Ast/Declarations/TranslationUnitDeclaration.hpp"
#include "Hyper/Ast/Declarations/VariableDeclaration.hpp"
#include "Hyper/Ast/Expressions/BinaryExpression.hpp"
#include "Hyper/Ast/Expressions/CallExpression.hpp"
#include "Hyper/Ast/Expressions/ConditionalExpression.hpp"
#include "Hyper/Ast/Expressions/IdentifierExpression.hpp"
#include "Hyper/Ast/Expressions/CastExpression.hpp"
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
	ScopeValidator::ScopeValidator(Diagnostics &diagnostics, AstPtr &ast)
		: Validator(diagnostics, ast)
	{
	}

	void ScopeValidator::accept(FunctionDeclaration &declaration)
	{
		if (contains_symbol(declaration.identifier().value))
		{
			const std::string error = Formatter::format(
				"redefinition of identifier '{}'", declaration.identifier().value);
			m_diagnostics.error(declaration.identifier().range, error);
		}

		const Symbol symbol = {
			.identifier = declaration.identifier().value,
			.kind = Symbol::Kind::Function,
			.type = declaration.return_type(),
			.range = declaration.identifier().range,
		};

		m_symbols.emplace_back(symbol);

		declaration.body()->validate(*this);
	}

	void ScopeValidator::accept(TranslationUnitDeclaration &declaration)
	{
		for (const auto &translation_unit_declaration : declaration.declarations())
		{
			translation_unit_declaration->validate(*this);
		}
	}

	void ScopeValidator::accept(VariableDeclaration &declaration)
	{
		if (contains_symbol(declaration.identifier().value))
		{
			const std::string error = Formatter::format(
				"redefinition of identifier '{}'", declaration.identifier().value);
			m_diagnostics.error(declaration.identifier().range, error);
		}

		const Symbol symbol = {
			.identifier = declaration.identifier().value,
			.kind = Symbol::Kind::Variable,
			.type = declaration.type(),
			.range = declaration.identifier().range,
		};

		m_symbols.emplace_back(symbol);

		if (declaration.expression() == nullptr)
		{
			return;
		}

		declaration.expression()->validate(*this);
	}

	void ScopeValidator::accept(BinaryExpression &expression)
	{
		expression.left()->validate(*this);
		expression.right()->validate(*this);
	}

	void ScopeValidator::accept(CallExpression &expression)
	{
		if (!contains_symbol(expression.identifier().value, Symbol::Kind::Function))
		{
			const std::string error = Formatter::format(
				"use of undeclared function '{}'", expression.identifier().value);
			m_diagnostics.error(expression.identifier().range, error);
		}
	}

	void ScopeValidator::accept(CastExpression &expression)
	{
		expression.expression()->validate(*this);
	}

	void ScopeValidator::accept(ConditionalExpression &expression)
	{
		expression.condition()->validate(*this);
		expression.true_expression()->validate(*this);
		expression.false_expression()->validate(*this);
	}

	void ScopeValidator::accept(IdentifierExpression &expression)
	{
		if (!contains_symbol(expression.identifier().value, Symbol::Kind::Variable))
		{
			const std::string error = Formatter::format(
				"use of undeclared identifier '{}'", expression.identifier().value);
			m_diagnostics.error(expression.identifier().range, error);
		}
	}

	void ScopeValidator::accept(UnaryExpression &expression)
	{
		expression.expression()->validate(*this);
	}

	void ScopeValidator::accept(BoolLiteral &)
	{
	}

	void ScopeValidator::accept(IntegerLiteral &)
	{
	}

	void ScopeValidator::accept(StringLiteral &)
	{
	}

	void ScopeValidator::accept(AssignStatement &statement)
	{
		if (!contains_symbol(statement.identifier().value, Symbol::Kind::Variable))
		{
			const std::string error = Formatter::format(
				"use of undeclared identifier '{}'", statement.identifier().value);
			m_diagnostics.error(statement.identifier().range, error);
		}

		statement.expression()->validate(*this);
	}

	void ScopeValidator::accept(CompoundAssignStatement &statement)
	{
		if (!contains_symbol(statement.identifier().value, Symbol::Kind::Variable))
		{
			const std::string error = Formatter::format(
				"use of undeclared identifier '{}'", statement.identifier().value);
			m_diagnostics.error(statement.identifier().range, error);
		}

		statement.expression()->validate(*this);
	}

	void ScopeValidator::accept(CompoundStatement &statement)
	{
		for (const auto &compound_statement : statement.statements())
		{
			compound_statement->validate(*this);
		}
	}

	void ScopeValidator::accept(ExpressionStatement &statement)
	{
		statement.expression()->validate(*this);
	}

	void ScopeValidator::accept(IfStatement &statement)
	{
		statement.condition()->validate(*this);
		statement.true_body()->validate(*this);

		if (statement.false_body() != nullptr)
		{
			statement.false_body()->validate(*this);
		}
	}

	void ScopeValidator::accept(ReturnStatement &statement)
	{
		statement.expression()->validate(*this);
	}

	void ScopeValidator::accept(WhileStatement &statement)
	{
		statement.condition()->validate(*this);
		statement.body()->validate(*this);
	}

	bool ScopeValidator::contains_symbol(
		const std::string &identifier,
		Symbol::Kind symbol_kind) const
	{
		for (const Symbol &symbol : m_symbols)
		{
			if (symbol.identifier != identifier)
			{
				continue;
			}

			if (symbol_kind != Symbol::Kind::Invalid && symbol.kind != symbol_kind)
			{
				continue;
			}

			return true;
		}

		return false;
	}

	std::vector<Symbol> ScopeValidator::symbols() const
	{
		return m_symbols;
	}
} // namespace Hyper
