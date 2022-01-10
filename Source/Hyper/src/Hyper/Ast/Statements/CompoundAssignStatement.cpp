/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/CompoundAssignStatement.hpp"

#include "Hyper/Ast/Expression.hpp"
#include "Hyper/Validator.hpp"

namespace Hyper
{
	CompoundAssignStatement::CompoundAssignStatement(
		SourceRange range,
		Identifier identifier,
		CompoundAssignStatement::Operation operation,
		ExpressionPtr expression)
		: Statement(range)
		, m_identifier(std::move(identifier))
		, m_operation(operation)
		, m_expression(std::move(expression))
	{
	}

	void CompoundAssignStatement::dump(std::string_view prefix, bool self_last)
		const
	{
		AstNode::dump_self(prefix, self_last);

		AstNode::dump_node(*m_expression, prefix, self_last, true);
	}

	void CompoundAssignStatement::validate(Validator &validator)
	{
		validator.accept(*this);
	}

	Identifier CompoundAssignStatement::identifier() const
	{
		return m_identifier;
	}

	CompoundAssignStatement::Operation CompoundAssignStatement::operation() const
	{
		return m_operation;
	}

	const ExpressionPtr &CompoundAssignStatement::expression() const
	{
		return m_expression;
	}
} // namespace Hyper
