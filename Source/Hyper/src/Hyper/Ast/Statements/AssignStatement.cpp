/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/AssignStatement.hpp"

#include "Hyper/Ast/Expression.hpp"

namespace Hyper
{
	AssignStatement::AssignStatement(std::string name, ExpressionPtr expression)
		: m_name(std::move(name))
		, m_expression(std::move(expression))
	{
	}

	void AssignStatement::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);

		AstNode::dump_node(*m_expression, prefix, self_last, true);
	}

	AstNode::Category AssignStatement::class_category() const noexcept
	{
		return AstNode::Category::AssignStatement;
	}

	std::string_view AssignStatement::class_name() const noexcept
	{
		return "AssignStatement";
	}
} // namespace Hyper
