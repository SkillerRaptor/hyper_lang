/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Statements/Statement.hpp"

namespace Hyper
{
	std::string_view Statement::class_name() const noexcept
	{
		return "Statement";
	}
} // namespace Hyper
