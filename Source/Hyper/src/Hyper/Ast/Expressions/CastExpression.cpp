/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expressions/CastExpression.hpp"

#include "Hyper/Validator.hpp"

namespace Hyper
{
	CastExpression::CastExpression(
		SourceRange range,
		ExpressionPtr expression,
		Type type)
		: Expression(range)
		, m_expression(std::move(expression))
		, m_type(type)
	{
	}

	void CastExpression::dump(std::string_view prefix, bool self_last)
		const
	{
		AstNode::dump_self(prefix, self_last);

		AstNode::dump_node(*m_expression, prefix, self_last, true);
	}

	void CastExpression::validate(Validator &validator)
	{
		validator.accept(*this);
	}

	const ExpressionPtr &CastExpression::expression() const
	{
		return m_expression;
	}

	Type CastExpression::type() const
	{
		return m_type;
	}
} // namespace Hyper
