/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/expressions/expression.hpp"

namespace hyper
{
	class Literal : public Expression
	{
	public:
		explicit Literal(SourceRange source_range);

		constexpr std::string_view class_name() const override
		{
			return "Literal";
		}
	};
} // namespace hyper
