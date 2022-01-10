/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/Expression.hpp"

namespace Hyper
{
	class Literal : public Expression
	{
	public:
		explicit Literal(SourceRange range);

		constexpr std::string_view class_name() const noexcept override
		{
			return "Literal";
		}
	};
} // namespace Hyper
