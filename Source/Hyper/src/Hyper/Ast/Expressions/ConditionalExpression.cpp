/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expressions/ConditionalExpression.hpp"

namespace Hyper
{
	ConditionalExpression::ConditionalExpression(
		ExpressionPtr condition,
		ExpressionPtr true_expression,
		ExpressionPtr false_expression)
		: m_condition(std::move(condition))
		, m_true_expression(std::move(true_expression))
		, m_false_expression(std::move(false_expression))
	{
	}

	void ConditionalExpression::dump(std::string_view prefix, bool self_last)
		const
	{
		AstNode::dump_self(prefix, self_last);

		AstNode::dump_node(*m_condition, prefix, self_last, false);
		AstNode::dump_node(*m_true_expression, prefix, self_last, false);
		AstNode::dump_node(*m_false_expression, prefix, self_last, true);
	}

	AstNode::Category ConditionalExpression::class_category() const noexcept
	{
		return AstNode::Category::ConditionalExpression;
	}

	std::string_view ConditionalExpression::class_name() const noexcept
	{
		return "ConditionalExpression";
	}
} // namespace Hyper
