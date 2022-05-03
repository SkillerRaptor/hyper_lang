/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/statements/statement.hpp"

namespace hyper
{
	class Declaration : public Statement
	{
	public:
		explicit Declaration(SourceRange source_range);

		constexpr std::string_view class_name() const override
		{
			return "Declaration";
		}
	};
} // namespace hyper
