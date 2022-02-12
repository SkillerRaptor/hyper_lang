/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/expressions/cast_expression.hpp"

namespace hyper
{
	CastExpression::CastExpression(
		SourceRange source_range,
		Expression *expression,
		DataType type)
		: Expression(source_range)
		, m_expression(std::move(expression))
		, m_type(type)
	{
	}

	CastExpression::~CastExpression()
	{
		delete m_expression;
	}

	const Expression *CastExpression::expression() const
	{
		return m_expression;
	}

	DataType CastExpression::type() const
	{
		return m_type;
	}
} // namespace hyper
