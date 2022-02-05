/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/statement.hpp"

namespace hyper
{
	class Declaration : public Statement
	{
	public:
		explicit Declaration(SourceRange source_range);

		constexpr std::string_view class_name() const noexcept override
		{
			return "Declaration";
		}
	};
} // namespace hyper
