/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expressions/UnaryExpression.hpp"

#include "Hyper/Validator.hpp"

namespace Hyper
{
	UnaryExpression::UnaryExpression(
		SourceRange range,
		UnaryExpression::Operation operation,
		ExpressionPtr expression)
		: Expression(range)
		, m_operation(operation)
		, m_expression(std::move(expression))
	{
	}

	void UnaryExpression::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);

		AstNode::dump_node(*m_expression, prefix, self_last, true);
	}

	void UnaryExpression::validate(Validator &validator)
	{
		validator.accept(*this);
	}

	UnaryExpression::Operation UnaryExpression::operation() const
	{
		return m_operation;
	}

	const ExpressionPtr &UnaryExpression::expression() const
	{
		return m_expression;
	}
} // namespace Hyper
