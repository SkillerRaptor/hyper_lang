/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/statements/statement.hpp"

namespace hyper
{
	Statement::Statement(SourceRange source_range)
		: AstNode(source_range)
	{
	}
} // namespace hyper
