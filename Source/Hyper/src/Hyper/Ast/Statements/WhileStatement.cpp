/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/WhileStatement.hpp"

#include "Hyper/Ast/Expression.hpp"

namespace Hyper
{
	WhileStatement::WhileStatement(
		std::unique_ptr<Expression> condition,
		std::unique_ptr<Statement> body)
		: m_condition(std::move(condition))
		, m_body(std::move(body))
	{
	}

	void WhileStatement::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);

		AstNode::dump_node(*m_condition, prefix, self_last, false);
		AstNode::dump_node(*m_body, prefix, self_last, true);
	}

	AstNode::Category WhileStatement::class_category() const noexcept
	{
		return AstNode::Category::WhileStatement;
	}

	std::string_view WhileStatement::class_name() const noexcept
	{
		return "WhileStatement";
	}
} // namespace Hyper
