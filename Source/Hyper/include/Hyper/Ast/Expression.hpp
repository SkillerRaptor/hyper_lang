/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/AstNode.hpp"

namespace Hyper
{
	class Expression : public AstNode
	{
	public:
		explicit Expression(SourceRange range);

		constexpr std::string_view class_name() const noexcept override
		{
			return "Expression";
		}
	};
} // namespace Hyper
