/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expressions/IdentifierExpression.hpp"

namespace Hyper
{
	IdentifierExpression::IdentifierExpression(std::string name)
		: m_name(std::move(name))
	{
	}

	void IdentifierExpression::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);
	}

	AstNode::Category IdentifierExpression::class_category() const noexcept
	{
		return AstNode::Category::IdentifierExpression;
	}

	std::string_view IdentifierExpression::class_name() const noexcept
	{
		return "IdentifierExpression";
	}
} // namespace Hyper
