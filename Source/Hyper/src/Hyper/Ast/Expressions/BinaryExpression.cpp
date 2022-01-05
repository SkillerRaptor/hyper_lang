/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expressions/BinaryExpression.hpp"

#include "Hyper/Validator.hpp"

namespace Hyper
{
	BinaryExpression::BinaryExpression(
		Operation operation,
		ExpressionPtr left,
		ExpressionPtr right)
		: m_operation(operation)
		, m_left(std::move(left))
		, m_right(std::move(right))
	{
	}

	void BinaryExpression::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);

		AstNode::dump_node(*m_left, prefix, self_last, false);
		AstNode::dump_node(*m_right, prefix, self_last, true);
	}

	void BinaryExpression::validate(Validator &validator)
	{
		validator.accept(*this);
	}

	BinaryExpression::Operation BinaryExpression::operation() const
	{
		return m_operation;
	}

	const ExpressionPtr &BinaryExpression::left() const
	{
		return m_left;
	}

	const ExpressionPtr &BinaryExpression::right() const
	{
		return m_right;
	}
} // namespace Hyper
