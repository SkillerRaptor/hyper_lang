/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/literals/integer_literal.hpp"

namespace hyper
{
	IntegerLiteral::IntegerLiteral(SourceRange source_range, std::string integer)
		: Literal(source_range)
		, m_integer(std::move(integer))
	{
	}

	std::string_view IntegerLiteral::integer() const
	{
		return m_integer;
	}
} // namespace hyper
