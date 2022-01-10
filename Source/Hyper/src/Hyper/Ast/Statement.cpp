/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statement.hpp"

namespace Hyper
{
	Statement::Statement(SourceRange range)
		: AstNode(range)
	{
	}
} // namespace Hyper
