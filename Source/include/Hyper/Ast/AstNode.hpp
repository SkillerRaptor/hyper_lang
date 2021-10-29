/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstddef>

namespace Hyper
{
	class Generator;

	class AstNode
	{
	public:
		virtual ~AstNode() = default;

		virtual void generate(Generator &generator) const = 0;
		virtual void dump(size_t indent) const;

		virtual const char *class_name() const noexcept = 0;
	};
} // namespace Hyper
