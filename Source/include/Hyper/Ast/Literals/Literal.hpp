/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Expressions/Expression.hpp"

namespace Hyper
{
	class Literal : public Expression
	{
	public:
		const char *name() const noexcept override;
	};
} // namespace Hyper
