/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/WhileStatement.hpp"

#include "Hyper/Ast/Expression.hpp"
#include "Hyper/Validator.hpp"

namespace Hyper
{
	WhileStatement::WhileStatement(ExpressionPtr condition, StatementPtr body)
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

	void WhileStatement::validate(Validator &validator)
	{
		validator.accept(*this);
	}

	const ExpressionPtr &WhileStatement::condition() const
	{
		return m_condition;
	}

	const StatementPtr &WhileStatement::body() const
	{
		return m_body;
	}
} // namespace Hyper
