/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/expressions/unary_expression.hpp"

namespace hyper
{
	UnaryExpression::UnaryExpression(
		SourceRange source_range,
		UnaryExpression::Operation operation,
		Expression *expression)
		: Expression(source_range)
		, m_operation(operation)
		, m_expression(std::move(expression))
	{
	}

	UnaryExpression::~UnaryExpression()
	{
		delete m_expression;
	}

	UnaryExpression::Operation UnaryExpression::operation() const
	{
		return m_operation;
	}

	const Expression *UnaryExpression::expression() const
	{
		return m_expression;
	}
} // namespace hyper
