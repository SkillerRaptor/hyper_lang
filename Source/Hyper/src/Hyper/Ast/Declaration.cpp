/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "Hyper/Ast/Declaration.hpp"

namespace Hyper
{
	std::string_view Declaration::class_name() const noexcept
	{
		return "Declaration";
	}
} // namespace Hyper
