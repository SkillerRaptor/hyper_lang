/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "hyper_utilities/expected.hpp"
#include "hyper_utilities/formatter.hpp"

#include <concepts>
#include <string>
#include <string_view>

namespace hyper::utilities
{
	template <std::integral T>
	static constexpr size_t count_digits(T number) noexcept
	{
		size_t count = 0;
		while (number != 0)
		{
			number /= 10;
			++count;
		}

		return count;
	}

	static constexpr uint64_t hash_string(std::string_view string) noexcept
	{
		uint64_t result = 0xCBF29CE484222325;

		for (const char character : string)
		{
			result ^= static_cast<uint64_t>(character);
			result *= 1099511628211;
		}

		return result;
	}

	enum class FileError : uint8_t
	{
		FileIsDirectory = 0,
		FileNotFound,
		FileNotReadable,
	};

	Expected<std::string, FileError> read_file(std::string_view file);

	enum class StringError : uint8_t
	{
		OutOfRange = 0,
	};

	Expected<std::string_view, StringError> find_line(
		std::string_view text,
		size_t line);

	Expected<std::string, StringError> convert_wstring(std::wstring_view wstring);

	void replace_string(
		std::string &string,
		std::string_view search,
		std::string_view replacement);
} // namespace hyper::utilities
