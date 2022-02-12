/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/literals/literal.hpp"

namespace hyper
{
	Literal::Literal(SourceRange source_range)
		: Expression(source_range)
	{
	}
} // namespace hyper
