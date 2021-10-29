/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/Ast/AstNode.hpp"

namespace Hyper
{
	class Statement : public AstNode
	{
	public:
		~Statement() override = default;

		const char *class_name() const noexcept override;
	};
} // namespace Hyper
