/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Literals/IntegerLiteral.hpp"

namespace Hyper
{
	IntegerLiteral::IntegerLiteral(std::string integer)
		: m_integer(std::move(integer))
	{
	}

	void IntegerLiteral::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);
	}

	AstNode::Category IntegerLiteral::class_category() const noexcept
	{
		return AstNode::Category::IntegerLiteral;
	}

	std::string_view IntegerLiteral::class_name() const noexcept
	{
		return "IntegerLiteral";
	}
} // namespace Hyper
