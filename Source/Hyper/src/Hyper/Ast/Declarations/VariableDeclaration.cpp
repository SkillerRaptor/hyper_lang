/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Declarations/VariableDeclaration.hpp"

#include "Hyper/Ast/Expression.hpp"

namespace Hyper
{
	VariableDeclaration::VariableDeclaration(
		std::string name,
		VariableDeclaration::Mutable mutable_state,
		Type type,
		ExpressionPtr expression)
		: m_name(std::move(name))
		, m_mutable(mutable_state)
		, m_type(std::move(type))
		, m_expression(std::move(expression))
	{
		(void) m_mutable;
	}

	void VariableDeclaration::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);
	}

	AstNode::Category VariableDeclaration::class_category() const noexcept
	{
		return AstNode::Category::VariableDeclaration;
	}

	std::string_view VariableDeclaration::class_name() const noexcept
	{
		return "VariableDeclaration";
	}
} // namespace Hyper
