/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/statements/expression_statement.hpp"

#include "hyper/ast/expressions/expression.hpp"

namespace hyper
{
	ExpressionStatement::ExpressionStatement(
		SourceRange source_range,
		Expression *expression)
		: Statement(source_range)
		, m_expression(std::move(expression))
	{
	}

	ExpressionStatement::~ExpressionStatement()
	{
		delete m_expression;
	}

	const Expression *ExpressionStatement::expression() const
	{
		return m_expression;
	}
} // namespace hyper
