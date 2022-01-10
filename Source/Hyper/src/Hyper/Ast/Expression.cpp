/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expression.hpp"

namespace Hyper
{
	Expression::Expression(SourceRange range)
		: AstNode(range)
	{
	}
} // namespace Hyper
