/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expressions/BinaryExpression.hpp"

namespace Hyper
{
	BinaryExpression::BinaryExpression(
		Operation operation,
		std::unique_ptr<Expression> left,
		std::unique_ptr<Expression> right)
		: m_operation(operation)
		, m_left(std::move(left))
		, m_right(std::move(right))
	{
		(void) m_operation;
	}

	void BinaryExpression::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);

		AstNode::dump_node(*m_left, prefix, self_last, false);
		AstNode::dump_node(*m_right, prefix, self_last, true);
	}

	AstNode::Category BinaryExpression::class_category() const noexcept
	{
		return AstNode::Category::BinaryExpression;
	}

	std::string_view BinaryExpression::class_name() const noexcept
	{
		return "BinaryExpression";
	}
} // namespace Hyper
