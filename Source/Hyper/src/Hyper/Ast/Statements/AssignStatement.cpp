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
		std::string identifier,
		ExpressionPtr expression,
		SourceRange identifier_range)
		: m_identifier(std::move(identifier))
		, m_expression(std::move(expression))
		, m_identifier_range(identifier_range)
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

	std::string AssignStatement::identifier() const
	{
		return m_identifier;
	}

	const ExpressionPtr &AssignStatement::expression() const
	{
		return m_expression;
	}

	SourceRange AssignStatement::identifier_range() const
	{
		return m_identifier_range;
	}
} // namespace Hyper
