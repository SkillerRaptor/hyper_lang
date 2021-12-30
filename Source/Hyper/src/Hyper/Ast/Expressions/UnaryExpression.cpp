/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expressions/UnaryExpression.hpp"

namespace Hyper
{
	UnaryExpression::UnaryExpression(Kind kind, ExpressionPtr expression)
		: m_kind(kind)
		, m_expression(std::move(expression))
	{
		(void) m_kind;
	}

	void UnaryExpression::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);

		AstNode::dump_node(*m_expression, prefix, self_last, true);
	}

	AstNode::Category UnaryExpression::class_category() const noexcept
	{
		return AstNode::Category::UnaryExpression;
	}

	std::string_view UnaryExpression::class_name() const noexcept
	{
		return "UnaryExpression";
	}
} // namespace Hyper
