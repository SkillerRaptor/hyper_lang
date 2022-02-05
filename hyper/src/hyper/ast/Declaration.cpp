/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/ast/declaration.hpp"

namespace hyper
{
	Declaration::Declaration(SourceRange source_range)
		: Statement(source_range)
	{
	}
} // namespace hyper
