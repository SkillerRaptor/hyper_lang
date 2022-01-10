/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Literal.hpp"

namespace Hyper
{
	Literal::Literal(SourceRange range)
		: Expression(range)
	{
	}
} // namespace Hyper
