/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstddef>

namespace Hyper
{
	class AstNode
	{
	public:
		virtual ~AstNode() = default;

		virtual void dump(size_t indent) const;

		virtual const char *name() const noexcept;
	};
} // namespace Hyper
