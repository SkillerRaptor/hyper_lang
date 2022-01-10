/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Literals/BoolLiteral.hpp"

#include "Hyper/Validator.hpp"

namespace Hyper
{
	BoolLiteral::BoolLiteral(SourceRange range, bool boolean)
		: Literal(range)
		, m_boolean(boolean)
	{
	}

	void BoolLiteral::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);
	}

	void BoolLiteral::validate(Validator &validator)
	{
		validator.accept(*this);
	}

	bool BoolLiteral::boolean() const
	{
		return m_boolean;
	}
} // namespace Hyper
