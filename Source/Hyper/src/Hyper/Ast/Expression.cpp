/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Expression.hpp"

namespace Hyper
{
	std::string_view Expression::class_name() const noexcept
	{
		return "Expression";
	}
} // namespace Hyper
