/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/IfStatement.hpp"

#include "Hyper/Ast/Expression.hpp"
#include "Hyper/Validator.hpp"

namespace Hyper
{
	IfStatement::IfStatement(
		ExpressionPtr condition,
		StatementPtr true_body,
		StatementPtr false_body)
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
			AstNode::dump_node(*m_false_body, prefix, self_last, true);
		}
	}

	void IfStatement::validate(Validator &validator)
	{
		validator.accept(*this);
	}

	const ExpressionPtr &IfStatement::condition() const
	{
		return m_condition;
	}

	const StatementPtr &IfStatement::true_body() const
	{
		return m_true_body;
	}

	const StatementPtr &IfStatement::false_body() const
	{
		return m_false_body;
	}
} // namespace Hyper
