/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/literals/bool_literal.hpp"

namespace hyper
{
	BoolLiteral::BoolLiteral(SourceRange source_range, bool boolean)
		: Literal(source_range)
		, m_boolean(boolean)
	{
	}

	bool BoolLiteral::boolean() const
	{
		return m_boolean;
	}
} // namespace hyper
