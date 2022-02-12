/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/expressions/conditional_expression.hpp"

namespace hyper
{
	ConditionalExpression::ConditionalExpression(
		SourceRange source_range,
		Expression *condition,
		Expression *true_expression,
		Expression *false_expression)
		: Expression(source_range)
		, m_condition(std::move(condition))
		, m_true_expression(std::move(true_expression))
		, m_false_expression(std::move(false_expression))
	{
	}
	ConditionalExpression::~ConditionalExpression()
	{
		delete m_condition;
		delete m_true_expression;
		delete m_false_expression;
	}

	const Expression *ConditionalExpression::condition() const
	{
		return m_condition;
	}

	const Expression *ConditionalExpression::true_expression() const
	{
		return m_true_expression;
	}

	const Expression *ConditionalExpression::false_expression() const
	{
		return m_false_expression;
	}
} // namespace hyper
