/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/statements/compound_assign_statement.hpp"

#include "hyper/ast/expressions/expression.hpp"

namespace hyper
{
	CompoundAssignStatement::CompoundAssignStatement(
		SourceRange source_range,
		Identifier identifier,
		CompoundAssignStatement::Operation operation,
		Expression *expression)
		: Statement(source_range)
		, m_identifier(std::move(identifier))
		, m_operation(operation)
		, m_expression(std::move(expression))
	{
	}

	CompoundAssignStatement::~CompoundAssignStatement()
	{
		delete m_expression;
	}

	Identifier CompoundAssignStatement::identifier() const
	{
		return m_identifier;
	}

	CompoundAssignStatement::Operation CompoundAssignStatement::operation() const
	{
		return m_operation;
	}

	const Expression *CompoundAssignStatement::expression() const
	{
		return m_expression;
	}
} // namespace hyper
