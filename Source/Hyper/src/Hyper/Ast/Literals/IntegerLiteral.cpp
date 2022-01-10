/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Literals/IntegerLiteral.hpp"

#include "Hyper/Validator.hpp"

namespace Hyper
{
	IntegerLiteral::IntegerLiteral(SourceRange range, std::string integer)
		: Literal(range)
		, m_integer(std::move(integer))
	{
	}

	void IntegerLiteral::dump(std::string_view prefix, bool self_last) const
	{
		AstNode::dump_self(prefix, self_last);
	}

	void IntegerLiteral::validate(Validator &validator)
	{
		validator.accept(*this);
	}

	std::string IntegerLiteral::integer() const
	{
		return m_integer;
	}
} // namespace Hyper
