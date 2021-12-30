/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/CompoundAssignStatement.hpp"

#include "Hyper/Ast/Expression.hpp"

namespace Hyper
{
	CompoundAssignStatement::CompoundAssignStatement(
		std::string name,
		CompoundAssignStatement::Operation operation,
		ExpressionPtr expression)
		: m_name(std::move(name))
		, m_operation(operation)
		, m_expression(std::move(expression))
	{
		(void) m_operation;
	}

	void CompoundAssignStatement::dump(std::string_view prefix, bool self_last)
		const
	{
		AstNode::dump_self(prefix, self_last);

		AstNode::dump_node(*m_expression, prefix, self_last, true);
	}

	AstNode::Category CompoundAssignStatement::class_category() const noexcept
	{
		return AstNode::Category::CompoundAssignStatement;
	}

	std::string_view CompoundAssignStatement::class_name() const noexcept
	{
		return "CompoundAssignStatement";
	}
} // namespace Hyper
