/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>
#include <string>

namespace Hyper
{
	struct Type
	{
		enum class Kind : uint8_t
		{
			Invalid = 0,

			Bool,

			Int8,
			Int16,
			Int32,
			Int64,

			Uint8,
			Uint16,
			Uint32,
			Uint64,

			ISize,
			USize,

			Float32,
			Float64,

			String,
			Void,

			UserDefined,
		};

		std::string value;
		Kind kind = Kind::Invalid;
	};
} // namespace Hyper
