/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expressions/UnaryExpression.hpp"

#include "Hyper/Validator.hpp"

namespace Hyper
{
	UnaryExpression::UnaryExpression(Kind kind, ExpressionPtr expression)
		: m_kind(kind)
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

	UnaryExpression::Kind UnaryExpression::kind() const
	{
		return m_kind;
	}

	const ExpressionPtr &UnaryExpression::expression() const
	{
		return m_expression;
	}
} // namespace Hyper
