/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <ostream>

namespace Hyper
{
	enum class DataType : unsigned char
	{
		None = 0,

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

		Void
	};

	std::ostream &operator<<(std::ostream &ostream, const DataType &type);
} // namespace Hyper
