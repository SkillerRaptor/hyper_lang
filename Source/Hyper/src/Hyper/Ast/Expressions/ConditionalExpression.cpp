/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expressions/ConditionalExpression.hpp"

#include "Hyper/Validator.hpp"

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

	void ConditionalExpression::validate(Validator &validator)
	{
		validator.accept(*this);
	}

	const ExpressionPtr &ConditionalExpression::condition() const
	{
		return m_condition;
	}

	const ExpressionPtr &ConditionalExpression::true_expression() const
	{
		return m_true_expression;
	}

	const ExpressionPtr &ConditionalExpression::false_expression() const
	{
		return m_false_expression;
	}
} // namespace Hyper
