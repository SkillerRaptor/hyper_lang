/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstddef>
#include <ostream>

namespace Hyper
{
	struct SourceLocation
	{
		size_t line = 1;
		size_t column = 1;
		size_t length = 1;
		size_t start = 0;
	};

	std::ostream &operator<<(
		std::ostream &ostream,
		const SourceLocation &source_location);
} // namespace Hyper
