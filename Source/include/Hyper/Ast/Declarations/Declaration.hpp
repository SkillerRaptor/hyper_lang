/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Statements/Statement.hpp"

namespace Hyper
{
	class Declaration : public Statement
	{
	public:
		~Declaration() override = default;
	};
} // namespace Hyper
