/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/ast/ast_node.hpp"

namespace hyper
{
	class Expression : public AstNode
	{
	public:
		explicit Expression(SourceRange source_range);

		constexpr std::string_view class_name() const noexcept override
		{
			return "Expression";
		}
	};
} // namespace hyper
