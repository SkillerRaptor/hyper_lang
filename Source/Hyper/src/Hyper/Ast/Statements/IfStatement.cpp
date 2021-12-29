/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/IfStatement.hpp"

#include "Hyper/Ast/Expression.hpp"

namespace Hyper
{
	IfStatement::IfStatement(
		std::unique_ptr<Expression> condition,
		std::unique_ptr<Statement> true_body,
		std::unique_ptr<Statement> false_body)
		: m_condition(std::move(condition))
		, m_true_body(std::move(true_body))
		, m_false_body(std::move(false_body))
	{
	}

	void IfStatement::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);

		const bool false_body = m_false_body != nullptr;

		AstNode::dump_node(*m_condition, prefix, self_last, false);
		AstNode::dump_node(*m_true_body, prefix, self_last, !false_body);

		if (false_body)
		{
			AstNode::dump_node(*m_false_body, prefix, self_last, false);
		}
	}

	AstNode::Category IfStatement::class_category() const noexcept
	{
		return AstNode::Category::IfStatement;
	}

	std::string_view IfStatement::class_name() const noexcept
	{
		return "IfStatement";
	}
} // namespace Hyper
