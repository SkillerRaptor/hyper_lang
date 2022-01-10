/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/SourceRange.hpp"

#include <string>

namespace Hyper
{
	struct Identifier
	{
		std::string value;
		SourceRange range = {};
	};
} // namespace Hyper
