/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Literals/StringLiteral.hpp"

namespace Hyper
{
	StringLiteral::StringLiteral(std::string string)
		: m_string(std::move(string))
	{
	}

	void StringLiteral::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);
	}

	AstNode::Category StringLiteral::class_category() const noexcept
	{
		return AstNode::Category::StringLiteral;
	}

	std::string_view StringLiteral::class_name() const noexcept
	{
		return "StringLiteral";
	}
} // namespace Hyper
