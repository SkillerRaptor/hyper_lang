/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstddef>

namespace Hyper
{
	struct Position
	{
		size_t line = 0;
		size_t column = 0;
	};

	struct SourceRange
	{
		Position start = {};
		Position end = {};
	};
} // namespace Hyper
