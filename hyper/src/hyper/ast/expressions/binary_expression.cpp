/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/expressions/binary_expression.hpp"

namespace hyper
{
	BinaryExpression::BinaryExpression(
		SourceRange source_range,
		Operation operation,
		Expression *left,
		Expression *right)
		: Expression(source_range)
		, m_operation(operation)
		, m_left(std::move(left))
		, m_right(std::move(right))
	{
	}

	BinaryExpression::~BinaryExpression()
	{
		delete m_left;
		delete m_right;
	}

	BinaryExpression::Operation BinaryExpression::operation() const
	{
		return m_operation;
	}

	const Expression *BinaryExpression::left() const
	{
		return m_left;
	}

	const Expression *BinaryExpression::right() const
	{
		return m_right;
	}
} // namespace hyper
