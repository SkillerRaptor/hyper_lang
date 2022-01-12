/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "Hyper/FixedString.hpp"

namespace Hyper::Utils
{
	template <FixedString string>
	constexpr uint64_t hash_string()
	{
		uint64_t result = 0xCBF29CE484222325;

		for (const char character : string)
		{
			result ^= static_cast<uint64_t>(character);
			result *= 1099511628211;
		}

		return result;
	}

	template <typename T>
	constexpr uint64_t hash_string(T string)
	{
		uint64_t result = 0xCBF29CE484222325;

		for (const char character : string)
		{
			result ^= static_cast<uint64_t>(character);
			result *= 1099511628211;
		}

		return result;
	}
} // namespace Hyper::Utils
