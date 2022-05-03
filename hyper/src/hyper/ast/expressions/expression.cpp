/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/expressions/expression.hpp"

namespace hyper
{
	Expression::Expression(SourceRange source_range)
		: AstNode(source_range)
	{
	}
} // namespace hyper
