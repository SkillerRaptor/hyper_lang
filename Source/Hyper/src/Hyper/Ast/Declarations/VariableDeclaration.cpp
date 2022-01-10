/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Declarations/VariableDeclaration.hpp"

#include "Hyper/Ast/Expression.hpp"
#include "Hyper/Validator.hpp"

namespace Hyper
{
	VariableDeclaration::VariableDeclaration(
		SourceRange range,
		Identifier identifier,
		VariableDeclaration::MutableState mutable_state,
		Type type,
		ExpressionPtr expression)
		: Declaration(range)
		, m_identifier(std::move(identifier))
		, m_mutable_state(mutable_state)
		, m_type(std::move(type))
		, m_expression(std::move(expression))
	{
	}

	void VariableDeclaration::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);
	}

	void VariableDeclaration::validate(Validator &validator)
	{
		validator.accept(*this);
	}

	Identifier VariableDeclaration::identifier() const
	{
		return m_identifier;
	}

	VariableDeclaration::MutableState VariableDeclaration::mutable_state() const
	{
		return m_mutable_state;
	}

	Type VariableDeclaration::type() const
	{
		return m_type;
	}

	const ExpressionPtr &VariableDeclaration::expression() const
	{
		return m_expression;
	}
} // namespace Hyper
