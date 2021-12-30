/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/ExpressionStatement.hpp"

#include "Hyper/Ast/Expression.hpp"

namespace Hyper
{
	ExpressionStatement::ExpressionStatement(ExpressionPtr expression)
		: m_expression(std::move(expression))
	{
	}

	void ExpressionStatement::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);

		AstNode::dump_node(*m_expression, prefix, self_last, true);
	}

	AstNode::Category ExpressionStatement::class_category() const noexcept
	{
		return AstNode::Category::ExpressionStatement;
	}

	std::string_view ExpressionStatement::class_name() const noexcept
	{
		return "ExpressionStatement";
	}
} // namespace Hyper
