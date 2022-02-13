/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <type_traits>

namespace hyper
{
	template <typename From, typename To>
	concept ConvertibleTo = std::is_convertible_v<From, To>;

	class Utilities
	{
	public:
		static constexpr uint64_t hash(std::string_view string) noexcept
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
		requires std::is_integral_v<T>
		static constexpr T count_digits(T number) noexcept
		{
			T count = 0;
			while (number != 0)
			{
				number /= 10;
				++count;
			}

			return count;
		}

		static std::string replace_string(
			std::string string,
			std::string_view search,
			std::string_view replacement)
		{
			size_t position = 0;
			while ((position = string.find(search, position)) != std::string::npos)
			{
				string.replace(position, search.length(), replacement);
				position += replacement.length();
			}
			return string;
		}

		static std::string read_line(std::string_view text, size_t line) noexcept
		{
			size_t start = std::numeric_limits<size_t>::max();
			size_t length = 0;

			size_t current_line = 1;
			for (size_t i = 0; i < text.length(); ++i)
			{
				const char character = text[i];
				if (current_line == line)
				{
					if (start == std::numeric_limits<size_t>::max())
					{
						start = i;
					}

					if (character != '\n')
					{
						++length;
					}
				}

				if (character == '\n' && ++current_line == (line + 1))
				{
					break;
				}
			}

			std::string string(text.substr(start, length));
			string = replace_string(string, "\t", "  ");

			return string;
		}
	};
} // namespace hyper
