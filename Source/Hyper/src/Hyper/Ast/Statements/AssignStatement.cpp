/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/AssignStatement.hpp"

#include "Hyper/Ast/Expression.hpp"
#include "Hyper/Validator.hpp"

namespace Hyper
{
	AssignStatement::AssignStatement(
		SourceRange range,
		Identifier identifier,
		ExpressionPtr expression)
		: Statement(range)
		, m_identifier(std::move(identifier))
		, m_expression(std::move(expression))
	{
	}

	void AssignStatement::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);

		AstNode::dump_node(*m_expression, prefix, self_last, true);
	}

	void AssignStatement::validate(Validator &validator)
	{
		validator.accept(*this);
	}

	Identifier AssignStatement::identifier() const
	{
		return m_identifier;
	}

	const ExpressionPtr &AssignStatement::expression() const
	{
		return m_expression;
	}
} // namespace Hyper
