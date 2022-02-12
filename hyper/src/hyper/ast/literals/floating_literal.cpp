/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/literals/floating_literal.hpp"

namespace hyper
{
	FloatingLiteral::FloatingLiteral(
		SourceRange source_range,
		std::string floating)
		: Literal(source_range)
		, m_floating(std::move(floating))
	{
	}

	std::string_view FloatingLiteral::floating() const
	{
		return m_floating;
	}
} // namespace hyper
