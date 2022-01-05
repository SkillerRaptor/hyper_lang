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
		std::string identifier,
		VariableDeclaration::Mutable mutable_state,
		Type type,
		ExpressionPtr expression,
		SourceRange identifier_range,
		SourceRange type_range)
		: m_identifier(std::move(identifier))
		, m_mutable(mutable_state)
		, m_type(std::move(type))
		, m_expression(std::move(expression))
		, m_identifier_range(identifier_range)
		, m_type_range(type_range)
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

	std::string VariableDeclaration::identifier() const
	{
		return m_identifier;
	}

	VariableDeclaration::Mutable VariableDeclaration::is_mutable() const
	{
		return m_mutable;
	}

	Type VariableDeclaration::type() const
	{
		return m_type;
	}

	const ExpressionPtr &VariableDeclaration::expression() const
	{
		return m_expression;
	}

	SourceRange VariableDeclaration::identifier_range() const
	{
		return m_identifier_range;
	}

	SourceRange VariableDeclaration::type_range() const
	{
		return m_type_range;
	}
} // namespace Hyper
