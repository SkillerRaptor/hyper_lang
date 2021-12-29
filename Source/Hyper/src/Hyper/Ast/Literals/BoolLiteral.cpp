/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Literals/BoolLiteral.hpp"

namespace Hyper
{
	BoolLiteral::BoolLiteral(bool boolean)
		: m_boolean(boolean)
	{
		(void) m_boolean;
	}

	void BoolLiteral::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);
	}

	AstNode::Category BoolLiteral::class_category() const noexcept
	{
		return AstNode::Category::BoolLiteral;
	}

	std::string_view BoolLiteral::class_name() const noexcept
	{
		return "BoolLiteral";
	}
} // namespace Hyper
