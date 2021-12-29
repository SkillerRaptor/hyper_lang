/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Literal.hpp"

namespace Hyper
{
	std::string_view Literal::class_name() const noexcept
	{
		return "Literal";
	}
} // namespace Hyper
