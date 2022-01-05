/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/ExpressionStatement.hpp"

#include "Hyper/Ast/Expression.hpp"
#include "Hyper/Validator.hpp"

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

	void ExpressionStatement::validate(Validator &validator)
	{
		validator.accept(*this);
	}

	const ExpressionPtr &ExpressionStatement::expression() const
	{
		return m_expression;
	}
} // namespace Hyper
