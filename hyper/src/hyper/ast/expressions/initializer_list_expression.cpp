/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/expressions/initializer_list_expression.hpp"

namespace hyper
{
	InitializerListExpression::InitializerListExpression(
		SourceRange source_range,
		std::vector<Expression *> expressions)
		: Expression(source_range)
		, m_expressions(expressions)
	{
	}

	InitializerListExpression::~InitializerListExpression()
	{
		for (const Expression *expression : m_expressions)
		{
			delete expression;
		}
	}

	std::span<Expression *const> InitializerListExpression::expressions() const
	{
		return m_expressions;
	}
} // namespace hyper
