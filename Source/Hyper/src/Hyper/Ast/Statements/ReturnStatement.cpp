/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/ReturnStatement.hpp"

#include "Hyper/Ast/Expression.hpp"

namespace Hyper
{
	ReturnStatement::ReturnStatement(ExpressionPtr expression)
		: m_expression(std::move(expression))
	{
	}

	void ReturnStatement::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);

		AstNode::dump_node(*m_expression, prefix, self_last, true);
	}

	AstNode::Category ReturnStatement::class_category() const noexcept
	{
		return AstNode::Category::ReturnStatement;
	}

	std::string_view ReturnStatement::class_name() const noexcept
	{
		return "ReturnStatement";
	}
} // namespace Hyper
