/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/statement.hpp"

namespace hyper
{
	Statement::Statement(SourceRange source_range)
		: AstNode(source_range)
	{
	}
} // namespace hyper
