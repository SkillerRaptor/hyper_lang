/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <ostream>

namespace Hyper
{
	enum class Type : unsigned char
	{
		None = 0,

		Int8,
		Int16,
		Int32,
		Int64,
		Uint8,
		Uint16,
		Uint32,
		Uint64,
		
		Void
	};

	std::ostream &operator<<(std::ostream &ostream, const Type &type);
} // namespace Hyper
