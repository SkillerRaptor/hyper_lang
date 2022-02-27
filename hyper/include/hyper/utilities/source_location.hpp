/*
 * Copyright (c) 2022-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <string_view>

namespace hyper
{
	class SourceLocation
	{
	public:
		static constexpr SourceLocation current(
			std::string_view file = __builtin_FILE(),
			std::string_view function = __builtin_FUNCTION(),
			uint64_t line = __builtin_LINE()) noexcept
		{
			SourceLocation source_location = {};
			source_location.m_file = file;
			source_location.m_function = function;
			source_location.m_line = line;

			return source_location;
		}

		constexpr SourceLocation() noexcept = default;

		constexpr std::string_view file_name() const noexcept
		{
			return m_file;
		}

		constexpr std::string_view function_name() const noexcept
		{
			return m_function;
		}

		constexpr uint64_t line() const noexcept
		{
			return m_line;
		}

	private:
		std::string_view m_file = "unknown";
		std::string_view m_function = "";
		uint64_t m_line = 0;
	};
} // namespace hyper
