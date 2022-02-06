/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper/data_type.hpp"
#include "hyper/source_range.hpp"

#include <string>

namespace hyper
{
	struct Symbol
	{
		enum class Kind : uint8_t
		{
			Invalid = 0,

			Function,
			Variable,
		};

		std::string name;
		std::string file;
		Kind kind = Kind::Invalid;
		DataType data_type = {};
		SourceRange source_range = {};
	};
} // namespace hyper
