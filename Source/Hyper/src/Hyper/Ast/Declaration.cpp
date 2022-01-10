/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Declaration.hpp"

namespace Hyper
{
	Declaration::Declaration(SourceRange range)
		: Statement(range)
	{
	}
} // namespace Hyper
