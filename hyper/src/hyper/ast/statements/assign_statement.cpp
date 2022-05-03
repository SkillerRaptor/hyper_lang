/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/statements/assign_statement.hpp"

#include "hyper/ast/expressions/expression.hpp"

namespace hyper
{
	AssignStatement::AssignStatement(
		SourceRange source_range,
		Identifier identifier,
		Expression *expression)
		: Statement(source_range)
		, m_identifier(std::move(identifier))
		, m_expression(std::move(expression))
	{
	}

	AssignStatement::~AssignStatement()
	{
		delete m_expression;
	}

	Identifier AssignStatement::identifier() const
	{
		return m_identifier;
	}

	const Expression *AssignStatement::expression() const
	{
		return m_expression;
	}
} // namespace hyper
