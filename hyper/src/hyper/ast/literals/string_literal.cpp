/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/literals/string_literal.hpp"

namespace hyper
{
	StringLiteral::StringLiteral(SourceRange source_range, std::string string)
		: Literal(source_range)
		, m_string(std::move(string))
	{
	}

	std::string_view StringLiteral::string() const
	{
		return m_string;
	}
} // namespace hyper
