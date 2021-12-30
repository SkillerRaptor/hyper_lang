/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expressions/CallExpression.hpp"

namespace Hyper
{
	CallExpression::CallExpression(std::string name, ExpressionList arguments)
		: m_name(std::move(name))
		, m_arguments(std::move(arguments))
	{
	}

	void CallExpression::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);

		for (const auto &argument : m_arguments)
		{
			const bool node_last = &argument == &m_arguments.back();
			AstNode::dump_node(*argument, prefix, self_last, node_last);
		}
	}

	AstNode::Category CallExpression::class_category() const noexcept
	{
		return AstNode::Category::CallExpression;
	}

	std::string_view CallExpression::class_name() const noexcept
	{
		return "CallExpression";
	}
} // namespace Hyper
