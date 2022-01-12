/*
 * Copyright (c) 2020-2021, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <algorithm>
#include <string_view>

namespace Hyper
{
	template <size_t N>
	class FixedString
	{
	public:
		constexpr FixedString(const char (&string)[N + 1]) noexcept
		{
			std::copy_n(string, N, content);
		}

		constexpr size_t size() const noexcept
		{
			return N;
		}

		constexpr const char *begin() const noexcept
		{
			return content;
		}

		constexpr const char *end() const noexcept
		{
			return content + size();
		}

		constexpr char operator[](size_t index) const noexcept
		{
			return content[index];
		}

		constexpr operator std::string_view() const noexcept
		{
			return std::string_view(content, size());
		}

		char content[N] = {};
	};

	template <typename CharT, size_t N>
	FixedString(const CharT (&)[N]) -> FixedString<N - 1>;

	template <size_t N>
	FixedString(FixedString<N>) -> FixedString<N>;
} // namespace Hyper
