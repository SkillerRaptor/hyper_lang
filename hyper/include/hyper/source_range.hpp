/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstddef>

namespace hyper
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
} // namespace hyper
