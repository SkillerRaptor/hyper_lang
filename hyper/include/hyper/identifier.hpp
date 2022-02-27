/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/source_range.hpp"

#include <string>

namespace hyper
{
	struct Identifier
	{
		std::string value;
		SourceRange source_range = {};

		// TODO: REMOVE THIS!
		size_t count = 0;
	};
} // namespace hyper
